// coding=utf-8
// file: source/cat.hpp
// coding=utf-8
// file: source/player.hpp

#pragma once

#include <vector>
#include <windows.h>
#include <wincon.h>
#include "consts.hpp"
#include "bfs.hpp"

class Cat {
    public:
        short x, y;
        bool is_move = false;

        Cat(short x, short y){
            this->x = x;
            this->y = y;
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

        void move_towards(short map[WIDTH][HEIGHT], Pos target){
            std::vector<Pos> path = bfs(map, Pos(x, y), target);
            short next_x = path[0].x;
            short next_y = path[0].y;
            if (next_x < x) {
                left(map);
            } else if (next_x > x) {
                right(map);
            } else if (next_y < y) {
                up(map);
            } else if (next_y > y) {
                down(map);
            }
        }
};

