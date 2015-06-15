//
//   Copyright (C) 2007 by sinamas <sinamas at users.sourceforge.net>
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

#include "fourp.h"
#include "gambatte.h"
#include "gamelink.h"
#include <stdlib.h>
#include <stdint.h>
#include <fstream>

namespace gambatte {

FourPAdapter::FourPAdapter() : byteTimerSecs_(0.001), cycleTimerSecs_(0.016), nextTimeout_(0), links_() { }

bool FourPAdapter::saveState(std::string path) {
    std::ofstream file(path.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if (!file.is_open()) {
        return false;
    }

    // note: don't save cur time / next timeout
    file.write((char *)&byteTimerSecs_, sizeof(byteTimerSecs_));
    file.write((char *)&cycleTimerSecs_, sizeof(cycleTimerSecs_));
    file.write((char *)&modeFlag_, sizeof(modeFlag_));
    file.write((char *)&bytesPerCycle_, sizeof(bytesPerCycle_));
    file.write((char *)&byteIdx_, sizeof(byteIdx_));

    for (int linkNum = 0; linkNum < 4; ++linkNum) {
        file.write((char *)links_[linkNum].txBuf, sizeof(links_[linkNum].txBuf));
        file.write((char *)links_[linkNum].rxBuf, sizeof(links_[linkNum].rxBuf));
        file.write((char *)&links_[linkNum].commTimeCode, sizeof(links_[linkNum].commTimeCode));
        file.write((char *)&links_[linkNum].commDataNumber, sizeof(links_[linkNum].commDataNumber));
        file.write((char *)&links_[linkNum].readingCommDataNumber, sizeof(links_[linkNum].readingCommDataNumber));
    }

    file.close();
    return true;
}

bool FourPAdapter::loadState(std::string path) {
    std::ifstream file(path.c_str(), std::ios::in | std::ios::binary);
    if (!file.is_open()) {
        return false;
    }

    // note: don't save cur time / next timeout
    file.read((char *)&byteTimerSecs_, sizeof(byteTimerSecs_));
    file.read((char *)&cycleTimerSecs_, sizeof(cycleTimerSecs_));
    file.read((char *)&modeFlag_, sizeof(modeFlag_));
    file.read((char *)&bytesPerCycle_, sizeof(bytesPerCycle_));
    file.read((char *)&byteIdx_, sizeof(byteIdx_));

    for (int linkNum = 0; linkNum < 4; ++linkNum) {
        file.read((char *)links_[linkNum].txBuf, sizeof(links_[linkNum].txBuf));
        file.read((char *)links_[linkNum].rxBuf, sizeof(links_[linkNum].rxBuf));
        file.read((char *)&links_[linkNum].commTimeCode, sizeof(links_[linkNum].commTimeCode));
        file.read((char *)&links_[linkNum].commDataNumber, sizeof(links_[linkNum].commDataNumber));
        file.read((char *)&links_[linkNum].readingCommDataNumber, sizeof(links_[linkNum].readingCommDataNumber));
    }

    file.close();
    return true;
}

void FourPAdapter::start() {
    moveToConnectionInformationMode();
}

void FourPAdapter::addPlayer(GB *gb) {
    for (int i = 0; i < 4; ++i) {
        if (links_[i].gb == NULL) {
            links_[i].gb = gb;
            links_[i].link = gb->createGameLink();
            return;
        }
    }
}

void FourPAdapter::moveToConnectionInformationMode() {
    bytesPerCycle_ = 4;
    for (uint8_t i = 0; i < 4; ++i) {
        // state:
        //   upper nibble: bitmask of connected units
        //   lower nibble: unit number (1-4)
        uint8_t state = i + 1;
        for (uint8_t j = 0; j < 4; ++j) {
            if (links_[j].gb != NULL) {
                state |= (1 << (j + 4));
            }
        }

        links_[i].txBuf[0] = 0xFE;
        links_[i].txBuf[1] = state;
        links_[i].txBuf[2] = state;
        links_[i].txBuf[3] = state;
    }

    byteIdx_ = 0;
    modeFlag_ = 0;
}

void FourPAdapter::moveToStartMode() {
    bytesPerCycle_ = 4;
    for (int i = 0; i < 4; ++i) {
        links_[i].txBuf[0] = 0xCC;
        links_[i].txBuf[1] = 0xCC;
        links_[i].txBuf[2] = 0xCC;
        links_[i].txBuf[3] = 0xCC;
    }

    // According to the patent, we're supposed to base the time/byte and the time/cycle on the "communication time
    // code", but this doesn't seem to work.  For some reason, games only work correctly when you use 20ms as the cycle
    // time (and they don't seemt to care about the byte time, so long as it's fast enough to fit within the 20ms).
    cycleTimerSecs_ = 20 / 1000.0;
    byteTimerSecs_ = cycleTimerSecs_ / (links_[0].commDataNumber * 5);

    byteIdx_ = 0;
    modeFlag_ = 1;
}

void FourPAdapter::moveToDataCommunicationMode() {
    bytesPerCycle_ = links_[0].commDataNumber * 4;

    // initialize tx buffer to contain all zeroes
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < bytesPerCycle_; ++j) {
            links_[i].txBuf[j] = 0;
        }
    }

    byteIdx_ = 0;
    modeFlag_ = 2;
}

void FourPAdapter::processRxData() {
    for (int i = 0; i < 4; ++i) {
        if (links_[i].readingCommDataNumber) {
            links_[i].commDataNumber = links_[i].rxBuf[0];
        }
        links_[i].readingCommDataNumber = false;
    }

    switch (modeFlag_) {
    case 0: // connection information mode
        for (int i = 0; i < 4; ++i) {
            // note that rxBuf[0] is garbage - it's a response to whatever we last sent, which means nothing
            if (links_[i].rxBuf[1] == 0x88 && links_[i].rxBuf[2] == 0x88) {
                // we received acknowledgement - save the communication time code
                links_[i].commTimeCode = links_[i].rxBuf[3];
                // note that we haven't received the 'communication data number' - that will be the first byte of the
                // next message
                links_[i].readingCommDataNumber = true;
            } else if (links_[i].rxBuf[1] == 0xAA && links_[i].rxBuf[2] == 0xAA && links_[i].rxBuf[3] == 0xAA) {
                // we received the start code, transition to start mode
                moveToStartMode();
            } else {
                // do nothing
            }
        }
        break;
    case 1: // start mode
        // in start mode, it doesn't matter what we receive - just move to data communication mode
        moveToDataCommunicationMode();
        break;
    case 2: // data communication mode mode
        // for each gameboy, the response will be in bytes 1 through N -
        // move them to a global transmission buffer in positions 0 through N-1
        for (int link = 0; link < 4; ++link) {
            for (int byte = 0; byte < links_[0].commDataNumber; ++byte) {
                links_[0].txBuf[(link * links_[0].commDataNumber) + byte] = links_[link].rxBuf[byte + 1];
            }
        }
        for (int link = 1; link < 4; ++link) {
            for (int i = 0; i < bytesPerCycle_; ++i) {
                links_[link].txBuf[i] = links_[0].txBuf[i];
            }
        }
        break;
    default:
        break; // TODO: reset mode
    }
}

void FourPAdapter::runByte() {
    // transmit / receive one data byte on each gameboy
    for (int link = 0; link < 4; ++link) {
        if (links_[link].gb == NULL) {
            continue;
        }

        links_[link].rxBuf[byteIdx_] = 0;
        for (int i = 0; i < 8; ++i) {
            bool inputBit = (links_[link].txBuf[byteIdx_] & (1 << (7 - i))) != 0;
            bool outputBit = links_[link].link->shift(inputBit);

            if (outputBit) {
                links_[link].rxBuf[byteIdx_] |= (1 << (7 - i));
            }
        }
    }

    byteIdx_++;
    if (byteIdx_ == bytesPerCycle_) {
        processRxData();
        byteIdx_ = 0;
    }
}

void FourPAdapter::runUntil(double timeSecs) {
    if (timeSecs < curTimeSecs_) {
        return;
    }

    curTimeSecs_ = timeSecs;
    while (curTimeSecs_ > nextTimeout_) {
        runByte();
        if (byteIdx_ == 0) {
            nextTimeout_ += cycleTimerSecs_ - ((bytesPerCycle_ - 1) * byteTimerSecs_);
        } else {
            nextTimeout_ += byteTimerSecs_;
        }
    }
}

}
