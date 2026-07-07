// coding=utf-8
// file: source/structs.hpp

#pragma once

struct Pos {
    short x;
    short y;
    Pos* parent;

    Pos(short x = 0, short y = 0, Pos* parent_ = nullptr) 
        : x(x), y(y), parent(parent_) {}
};
