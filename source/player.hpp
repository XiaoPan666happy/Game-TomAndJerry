// coding=utf-8
// file: source/player.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

class Player {
    public:
        short x, y;
        std::chrono::steady_clock::time_point last_move_time;
        std::chrono::steady_clock::time_point now_time;

        Player(short x, short y) {
            this->x = x;
            this->y = y;
            this->last_move_time = std::chrono::steady_clock::now();
            this->now_time = std::chrono::steady_clock::now();
        }

        void up(short map[WIDTH][HEIGHT]) {
            now_time = std::chrono::steady_clock::now();
            if (now_time - last_move_time >= std::chrono::milliseconds(TICK_TIME) &&
                 y > 0 && map[x][y-1] != MAP_WALL) {
                y--;
            }
        }

        void down(short map[WIDTH][HEIGHT]) {
            now_time = std::chrono::steady_clock::now();
            if (now_time - last_move_time >= std::chrono::milliseconds(TICK_TIME) &&
                 y < HEIGHT-1 && map[x][y+1] != MAP_WALL) {
                y++;
            }
        }

        void left(short map[WIDTH][HEIGHT]) {
            now_time = std::chrono::steady_clock::now();
            if (now_time - last_move_time >= std::chrono::milliseconds(TICK_TIME) &&
                 x > 0 && map[x-1][y] != MAP_WALL) {
                x--;
            }
        }

        void right(short map[WIDTH][HEIGHT]) {
            now_time = std::chrono::steady_clock::now();
            if (now_time - last_move_time >= std::chrono::milliseconds(TICK_TIME) &&
                 x < WIDTH-1 && map[x+1][y] != MAP_WALL) {
                x++;
            }
        }
};
