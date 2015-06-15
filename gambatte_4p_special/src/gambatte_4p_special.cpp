//
//   Copyright (C) 2015 by Giddeon Garber
//
//   This program is free software; you can redistribute it and/or modify
//   it under the terms of the GNU General Public License version 2 as
//   published by the Free Software Foundation.
//
//   This program is distributed in the hope that it will be useful,
//   but WITHOUT ANY WARRANTY; without even the implied warranty of
//   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//   GNU General Public License version 2 for more details.
//
//   You should have received a copy of the GNU General Public License
//   version 2 along with this program; if not, write to the
//   Free Software Foundation, Inc.,
//   51 Franklin St, Fifth Floor, Boston, MA  02110-1301, USA.
//

#include <cstdlib>
#include <cstdio>
#include <vector>
#include <unistd.h>
#include <glfw3.h>
#include <GL/glext.h>
#include "gambatte.h"
#include "fourp.h"
#include "gambatte_4p_special_palettes.h"

namespace gambatte4p {
using namespace gambatte;

class JoystickInput : public InputGetter {
public:
    JoystickInput(int const joy) : joy_(joy), curTimeSecs_(0) { }
    void update(double curTimeSecs);
    virtual unsigned operator()() { return state_; }

private:
    int const joy_;
    unsigned state_;
    bool failed_;
    double curTimeSecs_;
};

enum EmulationResult {
    EmulationResultMore,
    EmulationResultDone,
    EmulationResultSwapped,
};

class G4PCore {
public:
    G4PCore(int const player) : player_(player), input_(player), curTimeSecs_(0) { 
        gb_.setInputGetter(&input_);
    }

    LoadRes loadRom(std::string romPath) {
        return gb_.load(romPath, 0);
    }

    void saveState(std::string path) {
        if (!gb_.saveState(NULL, 0, path)) {
            fprintf(stderr, "Save state failed\n");
        }
    }

    void loadState(std::string path) {
        if (!gb_.loadState(path)) {
            fprintf(stderr, "Load state failed\n");
        }
    }

    void autoSetPallete() {
        std::string romTitle = gb_.romTitle();
        for (size_t i = 0; i < sizeof(gbcTitlePalettes) / sizeof(gbcTitlePalettes[0]); ++i) {
            if (gbcTitlePalettes[i].title.compare(romTitle) == 0) {
                for (int j = 0; j < 4; ++j) {
                    gb_.setDmgPaletteColor(BG_PALETTE, j, gbcTitlePalettes[i].p->bg[j]);
                    gb_.setDmgPaletteColor(SP1_PALETTE, j, gbcTitlePalettes[i].p->sp1[j]);
                    gb_.setDmgPaletteColor(SP2_PALETTE, j, gbcTitlePalettes[i].p->sp2[j]);
                }
            break;
            }
        }
    }

    bool calculateScreenPosition(int screenWidth, int screenHeight) {
        static const double gameboyAr = 160.0 / 144.0;
        static const double dividerH = 0.005; // % of the screen (horizontal divider - vertical is automatic)
        double screenAr = (double)screenWidth / ((double)screenHeight * (1.0 - dividerH));

        /* we only support wider screens (for simplicity) */
        if (screenAr < gameboyAr) {
            fprintf(stderr, "Screen isn't wide enough (%f < %f)\n", screenAr, gameboyAr);
            return false;
        }

        h_ = 0.5 - (dividerH / 2.0);
        w_ = h_ * (gameboyAr / screenAr);

        if (player_ < 2) {
            y_ = 0;
        } else {
            y_ = 0.5 + (dividerH / 2.0);
        }

        if (player_ % 2 == 0) {
            x_ = (0.5 - w_) / 2.0;
        } else {
            x_ = 0.5 + ((0.5 - w_) / 2.0);
        }

        return true;
    }

    EmulationResult emulate(double curTimeSecs) {
        if (curTimeSecs <= curTimeSecs_) {
            return EmulationResultDone;
        }

        input_.update(curTimeSecs);

        size_t samples = 4; /* 4 samples = 8 cycles */
        ptrdiff_t frameSwapOffset = gb_.runFor(videoBuf_, 160, audioBuf_, samples);
        curTimeSecs_ += samples / (35112.0 * 60.0); /* convert samples back to seconds */
        return (frameSwapOffset >= 0) ? EmulationResultSwapped : EmulationResultMore;
    }

    void draw() {
        glTexSubImage2D(
            GL_TEXTURE_2D,
            0,
            0, 
            256 - 144,
            160,
            144,
            GL_BGRA,
            GL_UNSIGNED_INT_8_8_8_8_REV,
            videoBuf_);
        glBegin(GL_QUADS);
        glTexCoord2d(0.0, 1 - (144.0 / 256.0));           glVertex2d(x_, y_);
        glTexCoord2d(160.0 / 256.0, 1 - (144.0 / 256.0)); glVertex2d(x_ + w_, y_);
        glTexCoord2d(160.0 / 256.0, 1.0);                 glVertex2d(x_ + w_, y_ + h_);
        glTexCoord2d(0.0, 1.0);                           glVertex2d(x_, y_ + h_);
        glEnd();
    }

    void link(G4PCore *other) {
        gb_.setGameLink(other->gb_.createGameLink());
        other->gb_.setGameLink(gb_.createGameLink());;
    }

    GameLink *createGameLink() {
        return gb_.createGameLink();
    }

    void addToAdapter(FourPAdapter *adapter) {
        adapter->addPlayer(&gb_);
    }

    inline double curTimeSecs() const {
        return curTimeSecs_;
    }

private:
    int const player_;
    GB gb_;
    JoystickInput input_;
    uint_least32_t videoBuf_[256 * 256];
    uint_least32_t audioBuf_[35112 + 2064];
    double curTimeSecs_;
    double x_;
    double y_;
    double w_;
    double h_;
};

class Gambatte4PSpecial {
public:
    int run(int numPlayers, const char *romPath);

    int numPlayers() { return numPlayers_; }
    const char *romPath() { return romPath_; }
    G4PCore **cores() { return cores_; }
    FourPAdapter *adapter() { return &adapter_; }

private:
    int numPlayers_;
    const char *romPath_;
    G4PCore **cores_;
    FourPAdapter adapter_;
};

void JoystickInput::update(double curTimeSecs) {
    if (failed_) {
        return;
    }

    if (curTimeSecs - curTimeSecs_ < 0.002) {
        return;
    }

    curTimeSecs_ = curTimeSecs;

    if (!glfwJoystickPresent(joy_)) {
        fprintf(stderr, "Could not find joystick for player %d!\n", joy_);
        failed_ = true;
        return;
    }

    int axesCount;
    int buttonCount;
    const float* axes = glfwGetJoystickAxes(joy_, &axesCount);
    const unsigned char* buttons = glfwGetJoystickButtons(joy_, &buttonCount);
    if (axesCount < 2 || buttonCount < 14) {
        fprintf(stderr, "Invalid controller configuration - not enough axes/buttons on joystick %d!\n", joy_);
        failed_ = true;
        return;
    }

    state_ = 0;
    if (axes[0] < -0.5)            state_ |= InputGetter::LEFT;
    if (axes[0] >  0.5)            state_ |= InputGetter::RIGHT;
    if (axes[1] < -0.5)            state_ |= InputGetter::UP;
    if (axes[1] >  0.5)            state_ |= InputGetter::DOWN;
    if (buttons[1]  == GLFW_PRESS) state_ |= InputGetter::A;
    if (buttons[0]  == GLFW_PRESS) state_ |= InputGetter::B;
    if (buttons[6]  == GLFW_PRESS) state_ |= InputGetter::SELECT;
    if (buttons[7]  == GLFW_PRESS) state_ |= InputGetter::START;
    if (buttons[13] == GLFW_PRESS) state_ |= InputGetter::LEFT;
    if (buttons[11] == GLFW_PRESS) state_ |= InputGetter::RIGHT;
    if (buttons[10] == GLFW_PRESS) state_ |= InputGetter::UP;
    if (buttons[12] == GLFW_PRESS) state_ |= InputGetter::DOWN;
}

static void glfwErrorCallback(int error, const char* description) {
    fprintf(stderr, "GLFW error %d: %s\n", error, description);
}

static void glfwKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    (void)scancode;
    (void)mods;
    char filename[1024];

    Gambatte4PSpecial *g4p = (Gambatte4PSpecial *)glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_S && action == GLFW_PRESS) {
        for (int p = 0; p < g4p->numPlayers(); ++p) {
            sprintf(filename, "%s.core%d.sav", g4p->romPath(), p);
            g4p->cores()[p]->saveState(filename);
        }
        sprintf(filename, "%s.adapter.sav", g4p->romPath());
        if (!g4p->adapter()->saveState(filename)) {
            fprintf(stderr, "Save adapter state failed\n");
        }
    }

    if (key == GLFW_KEY_L && action == GLFW_PRESS) {
        for (int p = 0; p < g4p->numPlayers(); ++p) {
            sprintf(filename, "%s.core%d.sav", g4p->romPath(), p);
            g4p->cores()[p]->loadState(filename);
        }
        sprintf(filename, "%s.adapter.sav", g4p->romPath());
        if (!g4p->adapter()->loadState(filename)) {
            fprintf(stderr, "Load adapter state failed\n");
        }
    }

    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}

int Gambatte4PSpecial::run(int numPlayers, const char *romPath) {
    numPlayers_ = numPlayers;
    romPath_ = romPath;

    cores_ = new G4PCore*[numPlayers];
    for (int i = 0; i < numPlayers; ++i) {
        cores_[i] = new G4PCore(i);
        LoadRes error = cores_[i]->loadRom(romPath);
        if (error != LOADRES_OK) {
            fprintf(stderr, "failed to load ROM %s: %s\n", romPath, to_string(error).c_str());
        }
        cores_[i]->autoSetPallete();
        cores_[i]->addToAdapter(&adapter_);
    }
    adapter_.start();

    if (glfwInit() != GL_TRUE) {
        fprintf(stderr, "failed to init GLFW\n");
        return EXIT_FAILURE;
    }

    glfwSetErrorCallback(glfwErrorCallback);

    GLFWmonitor* monitor = glfwGetPrimaryMonitor();
    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
    GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "Gambatte 4-Player Fun Times", monitor, NULL);
    if (window == NULL) {
        fprintf(stderr, "failed to create GLFW window\n");
        return EXIT_FAILURE;
    }

    glfwSetWindowUserPointer(window, this);

    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    glfwSetKeyCallback(window, glfwKeyCallback);

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    for (int i = 0; i < numPlayers; ++i) {
        if (!cores_[i]->calculateScreenPosition(width, height)) {
            return EXIT_FAILURE;
        }
    }    

    glMatrixMode(GL_PROJECTION);
    glOrtho(0, 1, 1, 0, 1, 0);
    glMatrixMode(GL_MODELVIEW);
    glEnable(GL_TEXTURE_2D);
    glLoadIdentity();

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 256, 256, 0, GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glfwSetTime(0);

    while (!glfwWindowShouldClose(window)) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        usleep(100); // 0.1ms
#pragma GCC diagnostic pop

        double curTime = glfwGetTime();

        bool anyFrameSwapped = false;
        bool allDone = false;
        while (!allDone) {
            double latestTime = 0;
            allDone = true;
            for (int i = 0; i < numPlayers; ++i) {
                switch (cores_[i]->emulate(curTime)) {
                    case EmulationResultMore:
                        allDone = false;
                        break;
                    case EmulationResultDone:
                        break;
                    case EmulationResultSwapped:
                        anyFrameSwapped = true;
                        break;
                }
                if (cores_[i]->curTimeSecs() > latestTime) {
                    latestTime = cores_[i]->curTimeSecs();
                }
            }
            if (numPlayers > 1) {
                adapter_.runUntil(latestTime);
            }
        }

        if (anyFrameSwapped) {
            /* a new frame was completed - draw it */
            for (int i = 0; i < numPlayers; ++i) {
                cores_[i]->draw();
            }
            glfwSwapBuffers(window);
        }

        glfwPollEvents();
    }

    return EXIT_SUCCESS;
}

}

int main(int argc, char **argv) {
    puts("Gambatte SDL 4-Player Special Amazing Version");
    if (argc <= 1) {
        fprintf(stderr, "player count / ROM path not specified\n");
        return EXIT_FAILURE;
    }
    gambatte4p::Gambatte4PSpecial g4p;
    return g4p.run(atoi(argv[1]), argv[2]);
}
