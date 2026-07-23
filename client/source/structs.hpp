// coding=utf-8
// file: client/source/structs.hpp

#pragma once

struct Pos {
    short x;
    short y;

    bool operator== (const Pos& other) const {
        return x == other.x && y == other.y;
    }

    bool operator!= (const Pos& other) const {
        return x != other.x || y != other.y;
    }
};
 