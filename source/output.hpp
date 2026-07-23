// coding=utf-8
// file: source/output.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

void draw_wall(HANDLE);
void draw_home(HANDLE);
void draw_food(HANDLE);
void draw_player(HANDLE);
void draw_cat(HANDLE);
void draw_ai(HANDLE);
void draw_airode(HANDLE);
void draw_mouse_hole(HANDLE);
void draw_empty(HANDLE);

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
            } else if (y == HEIGHT-1) {
                WriteConsoleW(hConsole, L"下", 1, &charsWritten, NULL);
            }
        }
    }
}

void clear_screen(HANDLE hConsole) {
    DWORD charsWritten;
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            SetConsoleCursorPosition(hConsole, {static_cast<short>(x*2), static_cast<short>(y)});
            draw_empty(hConsole);
        }
    }
}

void draw_screen(HANDLE hConsole, short screen[WIDTH][HEIGHT]) {
    DWORD charsWritten;
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(x*2), static_cast<short>(y)});
            if (screen[x][y] == MAP_WALL) {
                draw_wall(hConsole);
            } else if (screen[x][y] == MAP_HOME) {
                draw_home(hConsole);
            } else if (screen[x][y] == MAP_FOOD) {
                draw_food(hConsole);
            } else if (screen[x][y] == MAP_PLAYER) {
                draw_player(hConsole);
            } else if (screen[x][y] == MAP_ENEMY) {
                draw_cat(hConsole);
            } else if (screen[x][y] == MAP_AI) {
                draw_ai(hConsole);
            } else if (screen[x][y] == MAP_AIRODE) {
                draw_airode(hConsole);
            } else if (screen[x][y] == MAP_MOUSE_HOLE){
                draw_mouse_hole(hConsole);
            } else {
                draw_empty(hConsole);
            }
        }
    }
}

void draw_wall(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED);
    WriteConsoleW(hConsole, L"墙", 1, &charsWritten, NULL);
}

void draw_home(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_BLUE);
    WriteConsoleW(hConsole, L"家", 1, &charsWritten, NULL);
}

void draw_food(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    WriteConsoleW(hConsole, L"食", 1, &charsWritten, NULL);
}

void draw_player(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    WriteConsoleW(hConsole, L"鼠", 1, &charsWritten, NULL);
}

void draw_cat(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE);
    WriteConsoleW(hConsole, L"猫", 1, &charsWritten, NULL);
}

void draw_ai(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
    WriteConsoleW(hConsole, L"智", 1, &charsWritten, NULL);
}

void draw_airode(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, BACKGROUND_GREEN);
    WriteConsoleW(hConsole, L"  ", 2, &charsWritten, NULL);
}

void draw_mouse_hole(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, BACKGROUND_RED);
    WriteConsoleW(hConsole, L"  ", 2, &charsWritten, NULL);
}

void draw_empty(HANDLE hConsole) {
    DWORD charsWritten;
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    WriteConsoleW(hConsole, L"  ", 2, &charsWritten, NULL);
}
