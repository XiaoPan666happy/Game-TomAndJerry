// coding=utf-8
// file: source/player.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

class Player {
    public:
        short x, y;
        bool is_move = false;

        Player(short x, short y){
            this->x = x;
            this->y = y;
        }

        void draw(HANDLE hConsole){
            DWORD charsWritten;
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            SetConsoleCursorPosition(hConsole, {static_cast<short>(x*2), y});
            WriteConsoleW(hConsole, L"鼠", 1, &charsWritten, NULL);
        }

        void up(short map[WIDTH][HEIGHT]){
            if (y > 0 && map[x][y-1] != MAP_WALL) {
                y--;
                is_move = true;
            }
        }
        void down(short map[WIDTH][HEIGHT]){
            if (y < HEIGHT-1 && map[x][y+1] != MAP_WALL) {
                y++;
                is_move = true;
            }
        }
        void left(short map[WIDTH][HEIGHT]){
            if (x > 0 && map[x-1][y] != MAP_WALL) {
                x--;
                is_move = true;
            }
        }
        void right(short map[WIDTH][HEIGHT]){
            if (x < WIDTH-1 && map[x+1][y] != MAP_WALL) {
                x++;
                is_move = true;
            }
        }
};
