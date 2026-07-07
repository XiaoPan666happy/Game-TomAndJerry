// coding=utf-8
// file: source/player.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

class Player {
    public:
        short x, y;

        Player(short x, short y){
            this->x = x;
            this->y = y;
        }

        void up(short map[WIDTH][HEIGHT]){
            if (y > 0 && map[x][y-1] != MAP_WALL) {
                y--;
            }
        }

        void down(short map[WIDTH][HEIGHT]){
            if (y < HEIGHT-1 && map[x][y+1] != MAP_WALL) {
                y++;
            }
        }

        void left(short map[WIDTH][HEIGHT]){
            if (x > 0 && map[x-1][y] != MAP_WALL) {
                x--;
            }
        }

        void right(short map[WIDTH][HEIGHT]){
            if (x < WIDTH-1 && map[x+1][y] != MAP_WALL) {
                x++;
            }
        }
};
