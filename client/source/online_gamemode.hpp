// coding=utf-8
// file: client/source/online_gamemode.hpp

#include <windows.h>
#include <wincon.h>

#pragma once

void online_gamemode(HANDLE hConsole) {
    DWORD charsWritten;
    
    Sleep(200);
    SetConsoleCursorPosition(hConsole, COORD{0, 0});
    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
    WriteConsoleW(hConsole, L"功能正在开发", 6, &charsWritten, NULL);
}
