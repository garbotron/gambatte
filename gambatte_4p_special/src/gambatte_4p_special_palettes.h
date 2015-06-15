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

#ifndef GAMBATTE_4P_SPECIAL_PALETTES_H
#define GAMBATTE_4P_SPECIAL_PALETTES_H

#include <string>

struct GbcPalette {
    uint32_t const bg[4];
    uint32_t const sp1[4];
    uint32_t const sp2[4];
};

static GbcPalette const p005 = {
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 },
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 },
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 }
};

static GbcPalette const p006 = {
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 }
};

static GbcPalette const p007 = {
    { 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000 }
};

static GbcPalette const p008 = {
    { 0xA59CFF, 0xFFFF00, 0x006300, 0x000000 },
    { 0xA59CFF, 0xFFFF00, 0x006300, 0x000000 },
    { 0xA59CFF, 0xFFFF00, 0x006300, 0x000000 }
};

static GbcPalette const p012 = {
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 }
};

static GbcPalette const p013 = {
    { 0x000000, 0x008484, 0xFFDE00, 0xFFFFFF },
    { 0x000000, 0x008484, 0xFFDE00, 0xFFFFFF },
    { 0x000000, 0x008484, 0xFFDE00, 0xFFFFFF }
};

static GbcPalette const p016 = {
    { 0xFFFFFF, 0xA5A5A5, 0x525252, 0x000000 },
    { 0xFFFFFF, 0xA5A5A5, 0x525252, 0x000000 },
    { 0xFFFFFF, 0xA5A5A5, 0x525252, 0x000000 }
};

static GbcPalette const p017 = {
    { 0xFFFFA5, 0xFF9494, 0x9494FF, 0x000000 },
    { 0xFFFFA5, 0xFF9494, 0x9494FF, 0x000000 },
    { 0xFFFFA5, 0xFF9494, 0x9494FF, 0x000000 }
};

static GbcPalette const p100 = {
    { 0xFFFFFF, 0xADAD84, 0x42737B, 0x000000 },
    { 0xFFFFFF, 0xFF7300, 0x944200, 0x000000 },
    { 0xFFFFFF, 0xADAD84, 0x42737B, 0x000000 }
};

static GbcPalette const p10B = {
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p10D = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 }
};

static GbcPalette const p110 = {
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p11C = {
    { 0xFFFFFF, 0x7BFF31, 0x0063C5, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x0063C5, 0x000000 }
};

static GbcPalette const p20B = {
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p20C = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFC542, 0xFFD600, 0x943A00, 0x4A0000 }
};

static GbcPalette const p300 = {
    { 0xFFFFFF, 0xADAD84, 0x42737B, 0x000000 },
    { 0xFFFFFF, 0xFF7300, 0x944200, 0x000000 },
    { 0xFFFFFF, 0xFF7300, 0x944200, 0x000000 }
};

static GbcPalette const p304 = {
    { 0xFFFFFF, 0x7BFF00, 0xB57300, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p305 = {
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p306 = {
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p308 = {
    { 0xA59CFF, 0xFFFF00, 0x006300, 0x000000 },
    { 0xFF6352, 0xD60000, 0x630000, 0x000000 },
    { 0xFF6352, 0xD60000, 0x630000, 0x000000 }
};

static GbcPalette const p30A = {
    { 0xB5B5FF, 0xFFFF94, 0xAD5A42, 0x000000 },
    { 0x000000, 0xFFFFFF, 0xFF8484, 0x943A3A },
    { 0x000000, 0xFFFFFF, 0xFF8484, 0x943A3A }
};

static GbcPalette const p30C = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFC542, 0xFFD600, 0x943A00, 0x4A0000 },
    { 0xFFC542, 0xFFD600, 0x943A00, 0x4A0000 }
};

static GbcPalette const p30D = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p30E = {
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p30F = {
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p312 = {
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 }
};

static GbcPalette const p319 = {
    { 0xFFE6C5, 0xCE9C84, 0x846B29, 0x5A3108 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 }
};

static GbcPalette const p31C = {
    { 0xFFFFFF, 0x7BFF31, 0x0063C5, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p405 = {
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 },
    { 0xFFFFFF, 0x52FF00, 0xFF4200, 0x000000 },
    { 0xFFFFFF, 0x5ABDFF, 0xFF0000, 0x0000FF }
};

static GbcPalette const p406 = {
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFF9C00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0x5ABDFF, 0xFF0000, 0x0000FF }
};

static GbcPalette const p407 = {
    { 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0xFFFF00, 0xFF0000, 0x000000 },
    { 0xFFFFFF, 0x5ABDFF, 0xFF0000, 0x0000FF }
};

static GbcPalette const p500 = {
    { 0xFFFFFF, 0xADAD84, 0x42737B, 0x000000 },
    { 0xFFFFFF, 0xFF7300, 0x944200, 0x000000 },
    { 0xFFFFFF, 0x5ABDFF, 0xFF0000, 0x0000FF }
};

static GbcPalette const p501 = {
    { 0xFFFF9C, 0x94B5FF, 0x639473, 0x003A3A },
    { 0xFFC542, 0xFFD600, 0x943A00, 0x4A0000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p502 = {
    { 0x6BFF00, 0xFFFFFF, 0xFF524A, 0x000000 },
    { 0xFFFFFF, 0xFFFFFF, 0x63A5FF, 0x0000FF },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 }
};

static GbcPalette const p503 = {
    { 0x52DE00, 0xFF8400, 0xFFFF00, 0xFFFFFF },
    { 0xFFFFFF, 0xFFFFFF, 0x63A5FF, 0x0000FF },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 }
};

static GbcPalette const p508 = {
    { 0xA59CFF, 0xFFFF00, 0x006300, 0x000000 },
    { 0xFF6352, 0xD60000, 0x630000, 0x000000 },
    { 0x0000FF, 0xFFFFFF, 0xFFFF7B, 0x0084FF }
};

static GbcPalette const p509 = {
    { 0xFFFFCE, 0x63EFEF, 0x9C8431, 0x5A5A5A },
    { 0xFFFFFF, 0xFF7300, 0x944200, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p50B = {
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFFFF7B, 0x0084FF, 0xFF0000 }
};

static GbcPalette const p50C = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFC542, 0xFFD600, 0x943A00, 0x4A0000 },
    { 0xFFFFFF, 0x5ABDFF, 0xFF0000, 0x0000FF }
};

static GbcPalette const p50D = {
    { 0xFFFFFF, 0x8C8CDE, 0x52528C, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 }
};

static GbcPalette const p50E = {
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p50F = {
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 }
};

static GbcPalette const p510 = {
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p511 = {
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x00FF00, 0x318400, 0x004A00 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p512 = {
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p514 = {
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFF00, 0xFF0000, 0x630000, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 }
};

static GbcPalette const p515 = {
    { 0xFFFFFF, 0xADAD84, 0x42737B, 0x000000 },
    { 0xFFFFFF, 0xFFAD63, 0x843100, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

static GbcPalette const p518 = {
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 }
};

static GbcPalette const p51A = {
    { 0xFFFFFF, 0xFFFF00, 0x7B4A00, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 },
    { 0xFFFFFF, 0x7BFF31, 0x008400, 0x000000 }
};

static GbcPalette const p51C = {
    { 0xFFFFFF, 0x7BFF31, 0x0063C5, 0x000000 },
    { 0xFFFFFF, 0xFF8484, 0x943A3A, 0x000000 },
    { 0xFFFFFF, 0x63A5FF, 0x0000FF, 0x000000 }
};

struct GbcPaletteEntry {
    std::string const title;
    GbcPalette const *p;
};

static GbcPaletteEntry const gbcDirPalettes[] = {
    { "GBC - Blue", &p518 },
    { "GBC - Brown", &p012 },
    { "GBC - Dark Blue", &p50D },
    { "GBC - Dark Brown", &p319 },
    { "GBC - Dark Green", &p31C },
    { "GBC - Grayscale", &p016 },
    { "GBC - Green", &p005 },
    { "GBC - Inverted", &p013 },
    { "GBC - Orange", &p007 },
    { "GBC - Pastel Mix", &p017 },
    { "GBC - Red", &p510 },
    { "GBC - Yellow", &p51A },
};

static GbcPaletteEntry const gbcTitlePalettes[] = {
    { "ALLEY WAY", &p008 },
    { "ASTEROIDS/MISCMD", &p30E },
    { "BA.TOSHINDEN", &p50F },
    { "BALLOON KID", &p006 },
    { "BASEBALL", &p503 },
    { "BOY AND BLOB GB1", &p512 },
    { "BOY AND BLOB GB2", &p512 },
    { "BT2RAGNAROKWORLD", &p312 },
    { "DEFENDER/JOUST", &p50F },
    { "DMG FOOTBALL", &p30E },
    { "DONKEY KONG", &p306 },
    { "DONKEYKONGLAND", &p50C },
    { "DONKEYKONGLAND 2", &p50C },
    { "DONKEYKONGLAND 3", &p50C },
    { "DONKEYKONGLAND95", &p501 },
    { "DR.MARIO", &p20B },
    { "DYNABLASTER", &p30F },
    { "F1RACE", &p012 },
    { "G&W GALLERY", &p304 },
    { "GALAGA&GALAXIAN", &p013 },
    { "GAME&WATCH", &p012 },
    { "GAMEBOY GALLERY", &p304 },
    { "GAMEBOY GALLERY2", &p304 },
    { "GBWARS", &p500 },
    { "GOLF", &p30E },
    { "Game and Watch 2", &p304 },
    { "HOSHINOKA-BI", &p508 },
    { "JAMES  BOND  007", &p11C },
    { "KAERUNOTAMENI", &p10D },
    { "KEN GRIFFEY JR", &p31C },
    { "KID ICARUS", &p30D },
    { "KILLERINSTINCT95", &p50D },
    { "KINGOFTHEZOO", &p30F },
    { "KIRAKIRA KIDS", &p012 },
    { "KIRBY BLOCKBALL", &p508 },
    { "KIRBY DREAM LAND", &p508 },
    { "KIRBY'S PINBALL", &p308 },
    { "KIRBY2", &p508 },
    { "LOLO2", &p50F },
    { "MAGNETIC SOCCER", &p50E },
    { "MANSELL", &p012 },
    { "MARIO & YOSHI", &p305 },
    { "MARIO'S PICROSS", &p012 },
    { "MARIOLAND2", &p509 },
    { "MEGA MAN 2", &p50F },
    { "MEGAMAN", &p50F },
    { "MEGAMAN3", &p50F },
    { "METROID2", &p514 },
    { "MILLI/CENTI/PEDE", &p31C },
    { "MOGURANYA", &p300 },
    { "MYSTIC QUEST", &p50E },
    { "NETTOU KOF 95", &p50F },
    { "NEW CHESSMASTER", &p30F },
    { "OTHELLO", &p50E },
    { "PAC-IN-TIME", &p51C },
    { "PICROSS 2", &p012 },
    { "PINOCCHIO", &p20C },
    { "POKEBOM", &p30C },
    { "POKEMON BLUE", &p10B },
    { "POKEMON GREEN", &p11C },
    { "POKEMON RED", &p110 },
    { "POKEMON YELLOW", &p007 },
    { "QIX", &p407 },
    { "RADARMISSION", &p100 },
    { "ROCKMAN WORLD", &p50F },
    { "ROCKMAN WORLD2", &p50F },
    { "ROCKMANWORLD3", &p50F },
    { "SEIKEN DENSETSU", &p50E },
    { "SOCCER", &p502 },
    { "SOLARSTRIKER", &p013 },
    { "SPACE INVADERS", &p013 },
    { "STAR STACKER", &p012 },
    { "STAR WARS", &p512 },
    { "STAR WARS-NOA", &p512 },
    { "STREET FIGHTER 2", &p50F },
    { "SUPER MARIOLAND", &p30A },
    { "SUPER RC PRO-AM", &p50F },
    { "SUPERDONKEYKONG", &p501 },
    { "SUPERMARIOLAND3", &p500 },
    { "TENNIS", &p502 },
    { "TETRIS", &p007 },
    { "TETRIS ATTACK", &p405 },
    { "TETRIS BLAST", &p006 },
    { "TETRIS FLASH", &p407 },
    { "TETRIS PLUS", &p31C },
    { "TETRIS2", &p407 },
    { "THE CHESSMASTER", &p30F },
    { "TOPRANKINGTENNIS", &p502 },
    { "TOPRANKTENNIS", &p502 },
    { "TOY STORY", &p30E },
    { "TRIP WORLD", &p500 }, // unofficial
    { "VEGAS STAKES", &p50E },
    { "WARIO BLAST", &p31C },
    { "WARIOLAND2", &p515 },
    { "WAVERACE", &p50B },
    { "WORLD CUP", &p30E },
    { "X", &p016 },
    { "YAKUMAN", &p012 },
    { "YOSHI'S COOKIE", &p406 },
    { "YOSSY NO COOKIE", &p406 },
    { "YOSSY NO PANEPON", &p405 },
    { "YOSSY NO TAMAGO", &p305 },
    { "ZELDA", &p511 },
};

#endif