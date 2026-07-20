// coding=utf-8
// file: source/main.cpp

#include <random>
#include <vector>
#include <thread>
#include <array>
#include <chrono>
#include <sstream>
#include <string>
#include <mutex>
#include <functional>
#include <windows.h>
#include <wincon.h>
#include "consts.hpp"
#include "output.hpp"
#include "input.hpp"
#include "player.hpp"
#include "cat.hpp"
#include "structs.hpp"
#include "bfs_thread.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    if (hConsole == INVALID_HANDLE_VALUE) return 1;

    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(hConsole, &cursor_info);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    bool start_capital_is_not_on = false;
    if (!(GetAsyncKeyState(VK_CAPITAL) & 0x0001)) {
        start_capital_is_not_on = true;
        keybd_event(VK_CAPITAL, 0, 0, 0);
        Sleep(50);
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
    }

    draw_rect(hConsole);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    WriteConsoleW(hConsole, TEXT1, wcslen(TEXT1), &charsWritten, NULL);
    WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    WriteConsoleW(hConsole, TEXT0, wcslen(TEXT0), &charsWritten, NULL);
    wait_key(VK_RETURN);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    for (int i=0;i<(wcslen(TEXT1)+wcslen(TEXT0))*2;i++) {
        WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    }

    Sleep(200);
    SetConsoleCursorPosition(hConsole, COORD{static_cast<short>((WIDTH-wcslen(TEXT2)-wcslen(TEXT0))/2), HEIGHT/2});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    WriteConsoleW(hConsole, TEXT2, wcslen(TEXT2), &charsWritten, NULL);
    WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    WriteConsoleW(hConsole, TEXT0, wcslen(TEXT0), &charsWritten, NULL);
    wait_key(VK_RETURN);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});

    short map[WIDTH][HEIGHT] = {0};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<short> rand_x(1, WIDTH-2);
    std::uniform_int_distribution<short> rand_y(1, HEIGHT-2);
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            if (x==0 || x==WIDTH-1 || y==0 || y==HEIGHT-1) {
                map[x][y] = MAP_WALL;
            }
        }
    }
    for (int _=0;_<(WIDTH*HEIGHT/4);_++) {
        map[rand_x(gen)][rand_y(gen)] = MAP_WALL;
    }
    short food_x = rand_x(gen);
    short food_y = rand_y(gen);
    map[food_x][food_y] = MAP_FOOD;

    short home_x = rand_x(gen);
    short home_y = rand_y(gen);
    map[home_x][home_y] = MAP_HOME;

    short ai_x = rand_x(gen);
    short ai_y = rand_y(gen);
    map[ai_x][ai_y] = MAP_AI;

    std::uniform_int_distribution<short> rand_mouse_hole_index(0, NUM_OF_MOUSE_HOLE-1);
    std::array<Pos, NUM_OF_MOUSE_HOLE> mouse_holes_pos;
    Pos temp_hole_pos;
    for (int i = 0; i < NUM_OF_MOUSE_HOLE; i++) {
        temp_hole_pos.x = rand_x(gen);
        temp_hole_pos.y = rand_y(gen);
        mouse_holes_pos[i] = temp_hole_pos;
        map[temp_hole_pos.x][temp_hole_pos.y] = MAP_MOUSE_HOLE;
    }

    Player player(home_x, home_y);
    Cat cat(rand_x(gen), rand_y(gen));

    short screen[WIDTH][HEIGHT] = {0};

    bool is_get_food = false;
    bool is_not_get_food = true;
    bool is_get_ai = false;
    bool is_game_over = false;
    short msg_count = 0;
    std::vector<Pos> ai_path;

    std::chrono::steady_clock::time_point game_start_time;
    game_start_time = std::chrono::steady_clock::now();

    short last_hole_index = -1;
    
    std::thread cat_bfs_thread(bfs_thread, 
                               std::cref(is_game_over), 
                               std::cref(cat.x), 
                               std::cref(cat.y), 
                               std::cref(player.x), 
                               std::cref(player.y), 
                               std::ref(map), 
                               std::ref(cat.path));

    cat_bfs_thread.detach();

    while (!is_game_over) {
        is_not_get_food = ! is_get_food;

        // 获取食物
        if (player.x == food_x && player.y == food_y && map[food_x][food_y] == MAP_FOOD) {
            is_get_food = true;
            map[food_x][food_y] = 0;
            SetConsoleCursorPosition(hConsole, COORD{0, static_cast<short>(HEIGHT+msg_count)});
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            WriteConsoleW(hConsole, TEXT3, wcslen(TEXT3), &charsWritten, NULL);
            msg_count++;
        }

        // 回家
        if (is_get_food && player.x == home_x && player.y == home_y) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);

            SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT4)), HEIGHT/2});
            WriteConsoleW(hConsole, TEXT4, wcslen(TEXT4), &charsWritten, NULL);

            std::chrono::steady_clock::time_point game_end_time;
            game_end_time = std::chrono::steady_clock::now();
            unsigned long long use_time;
            use_time = std::chrono::duration_cast<std::chrono::seconds>(game_end_time-game_start_time).count();
            std::wstringstream msg_wss;
            msg_wss << L"通关用时 " << use_time << L"秒";
            std::wstring msg = msg_wss.str();
            SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-msg.length()), HEIGHT/2+1});
            WriteConsoleW(hConsole, msg.c_str(), msg.length(), &charsWritten, NULL);
            
            is_game_over = true;
            break;
        }

        // 死
        if (player.x == cat.x && player.y == cat.y) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT5)), HEIGHT/2});
            WriteConsoleW(hConsole, TEXT5, wcslen(TEXT5), &charsWritten, NULL);
            
            is_game_over = true;
            break;
        }

        // 获取寻路
        if (player.x == ai_x && player.y == ai_y && map[ai_x][ai_y] == MAP_AI) {
            is_get_ai = true;
            map[ai_x][ai_y] = 0;
            SetConsoleCursorPosition(hConsole, COORD{0, static_cast<short>(HEIGHT+msg_count)});
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            WriteConsoleW(hConsole, TEXT6, wcslen(TEXT6), &charsWritten, NULL);
            msg_count++;
        }

        // 老鼠洞
        for (Pos temp_hole_pos : mouse_holes_pos) {
            if (GetAsyncKeyState('F') & 0x8000 &&
                 temp_hole_pos.x == player.x && temp_hole_pos.y == player.y) {
                last_hole_index = rand_mouse_hole_index(gen);
                player.x = mouse_holes_pos[last_hole_index].x;
                player.y = mouse_holes_pos[last_hole_index].y;
            }
        }

        if (is_get_ai) {
            if (is_get_food) {
                ai_path = bfs(map, Pos{player.x, player.y}, Pos{home_x, home_y});
            } else {
                ai_path = bfs(map, Pos{player.x, player.y}, Pos{food_x, food_y});
            }
        }

        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            player.up(map);
        }
        if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            player.down(map);
        }
        if (GetAsyncKeyState(VK_LEFT) & 0x8000) {
            player.left(map);
        }
        if (GetAsyncKeyState(VK_RIGHT) & 0x8000) {
            player.right(map);
        }
        cat.move_towards(map);

        memcpy(screen, map, sizeof(map));
        for (int i=1;i<(short)ai_path.size()-1;i++) {
            screen[ai_path[i].x][ai_path[i].y] = MAP_AIRODE;
        }
        screen[player.x][player.y] = MAP_PLAYER;
        screen[cat.x][cat.y] = MAP_ENEMY;
        draw_screen(hConsole, screen);
    }

    if (start_capital_is_not_on) {
        keybd_event(VK_CAPITAL, 0, 0, 0);
        Sleep(50);
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    cursor_info = {1, 1};
    SetConsoleCursorInfo(hConsole, &cursor_info);
}
