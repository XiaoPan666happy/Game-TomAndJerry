// coding=utf-8
// file: source/draw_rect.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

void draw_rect(HANDLE hConsole) {
    DWORD charsWritten;
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            SetConsoleCursorPosition(hConsole, {static_cast<short>(x*2), static_cast<short>(y)});
            if ((x==0 || x==WIDTH-1) && (y==0 || y==HEIGHT-1)) {
                WriteConsoleW(hConsole, L"角", 1, &charsWritten, NULL);
            } else if (x == 0) {
                WriteConsoleW(hConsole, L"左", 1, &charsWritten, NULL);
            } else if (x == WIDTH-1) {
                WriteConsoleW(hConsole, L"右", 1, &charsWritten, NULL);
            } else if (y == 0) {
                WriteConsoleW(hConsole, L"上", 1, &charsWritten, NULL);
            } else if (y == HEIGHT-1){
                WriteConsoleW(hConsole, L"下", 1, &charsWritten, NULL);
            }
        }
    }
}

void draw_screen(HANDLE hConsole, short screen[WIDTH][HEIGHT]) {
    DWORD charsWritten;
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            SetConsoleCursorPosition(hConsole, {static_cast<short>(x*2), static_cast<short>(y)});
            if (screen[x][y] == MAP_WALL) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
                WriteConsoleW(hConsole, L"墙", 1, &charsWritten, NULL);
            } else if (screen[x][y] == MAP_HOME) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
                WriteConsoleW(hConsole, L"家", 1, &charsWritten, NULL);
            } else if (screen[x][y] == MAP_FOOD) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
                WriteConsoleW(hConsole, L"食", 1, &charsWritten, NULL);
            } else if (screen[x][y] == MAP_PLAYER) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                WriteConsoleW(hConsole, L"鼠", 1, &charsWritten, NULL);
            } else if (screen[x][y] == MAP_ENEMY) {
                SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
                WriteConsoleW(hConsole, L"猫", 1, &charsWritten, NULL);
            } else {
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
                WriteConsoleW(hConsole, L"  ", 1, &charsWritten, NULL);
            }
        }
    }
}
