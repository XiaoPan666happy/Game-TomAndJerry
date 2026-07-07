// coding=utf-8
// file: source/main.cpp

#include <random>
#include <vector>
#include <windows.h>
#include <wincon.h>
#include "consts.hpp"
#include "output.hpp"
#include "input.hpp"
#include "player.hpp"
#include "cat.hpp"
#include "structs.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8);
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    if (hConsole == INVALID_HANDLE_VALUE) return 1;

    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(hConsole, &cursor_info);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    draw_rect(hConsole);
    SetConsoleCursorPosition(hConsole, {0, HEIGHT});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    WriteConsoleW(hConsole, TEXT1, wcslen(TEXT1), &charsWritten, NULL);
    WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    WriteConsoleW(hConsole, TEXT0, wcslen(TEXT0), &charsWritten, NULL);
    wait_key(VK_RETURN);
    SetConsoleCursorPosition(hConsole, {0, HEIGHT});
    for (int i=0;i<(wcslen(TEXT1)+wcslen(TEXT0))*2;i++) {
        WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    }

    Sleep(200);
    SetConsoleCursorPosition(hConsole, {static_cast<short>((WIDTH-wcslen(TEXT2)-wcslen(TEXT0))/2), HEIGHT/2});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    WriteConsoleW(hConsole, TEXT2, wcslen(TEXT2), &charsWritten, NULL);
    WriteConsoleW(hConsole, " ", 1, &charsWritten, NULL);
    WriteConsoleW(hConsole, TEXT0, wcslen(TEXT0), &charsWritten, NULL);
    wait_key(VK_RETURN);
    SetConsoleCursorPosition(hConsole, {0, HEIGHT});

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

    Player player(home_x, home_y);
    Cat cat(rand_x(gen), rand_y(gen));

    short screen[WIDTH][HEIGHT] = {0};

    bool is_get_food = false;
    bool is_get_ai = false;
    std::vector<Pos> ai_path;
    while (true) {
        // 获取食物
        if (player.x == food_x && player.y == food_y) {
            is_get_food = true;
            SetConsoleCursorPosition(hConsole, {0, HEIGHT});
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            WriteConsoleW(hConsole, TEXT3, wcslen(TEXT3), &charsWritten, NULL);
        }

        // 回家
        if (is_get_food && player.x == home_x && player.y == home_y) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN);
            SetConsoleCursorPosition(hConsole, {static_cast<short>((WIDTH-wcslen(TEXT4))/2), HEIGHT/2});
            WriteConsoleW(hConsole, TEXT4, wcslen(TEXT4), &charsWritten, NULL);
            break;
        }

        // 死
        if (player.x == cat.x && player.y == cat.y) {
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
            SetConsoleCursorPosition(hConsole, {static_cast<short>((WIDTH-wcslen(TEXT5))/2), HEIGHT/2});
            WriteConsoleW(hConsole, TEXT5, wcslen(TEXT5), &charsWritten, NULL);
            break;
        }

        // 获取寻路
        if (player.x == ai_x && player.y == ai_y) {
            is_get_ai = true;
            map[ai_x][ai_y] = 0;
            SetConsoleCursorPosition(hConsole, {0, HEIGHT});
            SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            WriteConsoleW(hConsole, TEXT6, wcslen(TEXT6), &charsWritten, NULL);
        }

        if (is_get_ai) {
            if (is_get_food) {
                ai_path = bfs(map, Pos(player.x, player.y), Pos(home_x, home_y));
            } else {
                ai_path = bfs(map, Pos(player.x, player.y), Pos(food_x, food_y));
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
        cat.move_towards(map, Pos(player.x, player.y));

        memcpy(screen, map, sizeof(map));
        for (int i=0;i<ai_path.size();i++) {
            screen[ai_path[i].x][ai_path[i].y] = MAP_AIRODE;
        }
        screen[player.x][player.y] = MAP_PLAYER;
        screen[cat.x][cat.y] = MAP_ENEMY;
        draw_screen(hConsole, screen);
    }


    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    SetConsoleCursorPosition(hConsole, {0, HEIGHT});
    cursor_info = {1, 1};
    SetConsoleCursorInfo(hConsole, &cursor_info);
}
