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
#include "structs.hpp"

class Cat {
    public:
        short x, y;
        short index = 0;

        Cat(short x, short y){
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

        void move_towards(short map[WIDTH][HEIGHT], Pos target){
            if (index == 0) {
                std::vector<Pos> path = bfs(map, Pos{x, y}, target);
                if (path.size() <= 1) {
                    return ;
                }
                short next_x = path[1].x;
                short next_y = path[1].y;
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
            index++;
            index %= 3;
        }
};

