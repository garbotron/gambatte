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

// Emulator implementation of the Gameboy 4-player adapter DMG-07
// Most of the info for this came from the patent:
// https://www.google.com/patents/US5396225

#ifndef FOURP_H
#define FOURP_H

#include "gambatte.h"
#include <stdint.h>
#include <string>
#include <queue>

namespace gambatte {

class FourPAdapter {
public:
    FourPAdapter();
    void addPlayer(GB *gb);
    void start();
    void runUntil(double timeSecs);
    bool saveState(std::string path);
    bool loadState(std::string path);

private:
    void moveToConnectionInformationMode();
    void moveToStartMode();
    void moveToDataCommunicationMode();
    void processRxData();
    void runByte();

    double curTimeSecs_; // absolute current time in seconds
    double byteTimerSecs_; // timer interval in seconds per byte sent
    double cycleTimerSecs_; // timer interval in seconds per byte sent
    double nextTimeout_; // absolute time of next timeout in seconds
    uint8_t modeFlag_; // per the patent
    uint8_t bytesPerCycle_; // number of bytes to transmit per cycle
    uint8_t byteIdx_; // which byte index we are currently transmitting

    struct {
        GB *gb;
        GameLink *link;
        uint8_t txBuf[32];
        uint8_t rxBuf[32];

        // values communicated during connection information mode
        uint16_t commTimeCode; // time code, per figure 9B of the patent
        uint16_t commDataNumber; // bytes per data send, per figure 9B of the patent
        bool readingCommDataNumber; // true if we just received a 2x$88 recognition code
    } links_[4];
};

}

#endif
