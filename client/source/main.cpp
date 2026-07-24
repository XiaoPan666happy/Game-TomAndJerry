// coding=utf-8
// file: client/source/main.cpp

#include <windows.h>
#include <wincon.h>
#include "offline_gamemode.hpp"
#include "online_gamemode.hpp"
#include "consts.hpp"

int main() {
    SetConsoleOutputCP(CP_UTF8); // 设置控制台编码格式为utf-8
    // 获取控制台窗口句柄
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD charsWritten;
    if (hConsole == INVALID_HANDLE_VALUE) return 1;

    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor_info = {1, 0};
    SetConsoleCursorInfo(hConsole, &cursor_info);

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);

    // 自动开启大写锁定
    bool start_capital_is_not_on = false;
    if (!(GetAsyncKeyState(VK_CAPITAL) & 0x0001)) {
        start_capital_is_not_on = true;
        keybd_event(VK_CAPITAL, 0, 0, 0);
        Sleep(100);
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
    }

    clear_screen(hConsole);
    draw_rect(hConsole);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN);
    WriteConsoleW(hConsole, TEXT1, wcslen(TEXT1), &charsWritten, NULL);
    WriteConsoleW(hConsole, L" ", 1, &charsWritten, NULL);
    WriteConsoleW(hConsole, TEXT0, wcslen(TEXT0), &charsWritten, NULL);
    wait_key(VK_RETURN);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    for (int i=0;i<(wcslen(TEXT1)+wcslen(TEXT0)+1);i++) {
        WriteConsoleW(hConsole, L"  ", 2, &charsWritten, NULL);
    }

    Sleep(200);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT7)*2), HEIGHT/4});
    WriteConsoleW(hConsole, TEXT7, wcslen(TEXT7), &charsWritten, NULL);
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY);
    SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT10)*2), HEIGHT/4*3+2});
    WriteConsoleW(hConsole, TEXT10, wcslen(TEXT10), &charsWritten, NULL);
    short gamemode = GAMEMODE_OFFLINE;
    while (!(GetAsyncKeyState(VK_RETURN) & 0x8000)) {
        if (GetAsyncKeyState(VK_UP) & 0x8000) {
            gamemode = GAMEMODE_OFFLINE;
        } else if (GetAsyncKeyState(VK_DOWN) & 0x8000) {
            gamemode = GAMEMODE_ONLINE;
        }

        switch (gamemode) {
            case GAMEMODE_OFFLINE:
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT8)*2), HEIGHT/4*3});
                WriteConsoleW(hConsole, TEXT8, wcslen(TEXT8), &charsWritten, NULL);
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT9)*2), HEIGHT/4*3+1});
                WriteConsoleW(hConsole, TEXT9, wcslen(TEXT9), &charsWritten, NULL);
                break;
            case GAMEMODE_ONLINE:
                SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
                SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT8)*2), HEIGHT/4*3});
                WriteConsoleW(hConsole, TEXT8, wcslen(TEXT8), &charsWritten, NULL);
                SetConsoleTextAttribute(hConsole, BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE);
                SetConsoleCursorPosition(hConsole, COORD{static_cast<short>(WIDTH-wcslen(TEXT9)*2), HEIGHT/4*3+1});
                WriteConsoleW(hConsole, TEXT9, wcslen(TEXT9), &charsWritten, NULL);
                break;
        }
    }

    switch (gamemode) {
        case GAMEMODE_OFFLINE:
            offline_gamemode(hConsole);
            break;
        case GAMEMODE_ONLINE:
            online_gamemode(hConsole);
            break;
    }

    if (start_capital_is_not_on) {
        keybd_event(VK_CAPITAL, 0, 0, 0);
        Sleep(100);
        keybd_event(VK_CAPITAL, 0, KEYEVENTF_KEYUP, 0);
    }

    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN);
    SetConsoleCursorPosition(hConsole, COORD{0, HEIGHT});
    cursor_info = {1, 1};
    SetConsoleCursorInfo(hConsole, &cursor_info);
}
