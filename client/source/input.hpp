// coding=utf-8
// file: client/source/input.hpp

#pragma once

#include <windows.h>
#include <wincon.h>
#include "consts.hpp"

void wait_key(int vKey) {
    while (!(GetAsyncKeyState(vKey) & 0x8000)){}
}
