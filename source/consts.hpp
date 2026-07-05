// coding=utf-8
// file: source/consts.hpp

#pragma once

constexpr short WIDTH = 16*3;
constexpr short HEIGHT = 9*3;

constexpr short MAP_WALL = 1;
constexpr short MAP_HOME = 2;
constexpr short MAP_FOOD = 3;
constexpr short MAP_PLAYER = 4;
constexpr short MAP_ENEMY = 5;

constexpr wchar_t* TEXT0 = L"确认请按回车";
constexpr wchar_t* TEXT1 = L"请确认上面这个框能正常在您的屏幕中显示";
constexpr wchar_t* TEXT2 = L"游戏目标 上下左右移动鼠标 吃到食物后回到家里";
constexpr wchar_t* TEXT3 = L"玩家吃到了食物";
constexpr wchar_t* TEXT4 = L"玩家回到了家里 游戏结束 玩家获胜";
constexpr wchar_t* TEXT5 = L"猫抓住了玩家 游戏结束 玩家失败";

struct Pos {
    short x;
    short y;
    Pos* parent;

    Pos(short x, short y, Pos* parent_ = nullptr) : x(x), y(y), parent(parent_) {}
};
