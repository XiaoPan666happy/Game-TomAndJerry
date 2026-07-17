// coding=utf-8
// file: bfs_thread.hpp

#pragma once

#include <thread>
#include <mutex>
#include <vector>
#include "consts.hpp"
#include "structs.hpp"
#include "bfs.hpp"

void bfs_thread(const bool & is_game_over, 
                const short & start_x, 
                const short & start_y, 
                const short & target_x, 
                const short & target_y, 
                short map[WIDTH][HEIGHT], 
                std::vector<Pos> & path) {
    std::mutex mtx;
    while (!is_game_over) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        std::lock_guard<std::mutex> lock(mtx);
        path = bfs(map, Pos{start_x, start_y}, Pos{target_x, target_y});
    }
}
