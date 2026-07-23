// coding=utf-8
// file: source/cat.hpp

#pragma once

#include <vector>
#include <chrono>
#include <windows.h>
#include <wincon.h>
#include "consts.hpp"
#include "bfs.hpp"
#include "structs.hpp"

class Cat {
    public:
        short x, y;
        std::chrono::steady_clock::time_point last_move_time;
        std::chrono::steady_clock::time_point now_time;
        std::vector<Pos> path;

        Cat(short x, short y) {
            this->x = x;
            this->y = y;
            this->last_move_time = std::chrono::steady_clock::now();
            this->now_time = std::chrono::steady_clock::now();
        }

        void up(short map[WIDTH][HEIGHT]) {
            if (y > 0 && map[x][y-1] != MAP_WALL) {
                y--;
            }
        }

        void down(short map[WIDTH][HEIGHT]) {
            if (y < HEIGHT-1 && map[x][y+1] != MAP_WALL) {
                y++;
            }
        }

        void left(short map[WIDTH][HEIGHT]) {
            if (x > 0 && map[x-1][y] != MAP_WALL) {
                x--;
            }
        }

        void right(short map[WIDTH][HEIGHT]) {
            if (x < WIDTH-1 && map[x+1][y] != MAP_WALL) {
                x++;
            }
        }

        // 根据bfs自动移动
        void move_towards(short map[WIDTH][HEIGHT]) {
            now_time = std::chrono::steady_clock::now();
            if (now_time - last_move_time >= std::chrono::milliseconds(TICK_TIME * 3)) {
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
                last_move_time = std::chrono::steady_clock::now();
            }
        }
};

