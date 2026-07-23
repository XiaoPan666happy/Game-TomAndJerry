// coding=utf-8
// file: source/consts.hpp

#pragma once

constexpr short WIDTH = 16*3;
constexpr short HEIGHT = 9*3;

constexpr short TICK_TIME = 100; // ms

constexpr short MAP_WALL = 1;
constexpr short MAP_HOME = 2;
constexpr short MAP_FOOD = 3;
constexpr short MAP_PLAYER = 4;
constexpr short MAP_ENEMY = 5;
constexpr short MAP_AI = 6;
constexpr short MAP_AIRODE = 7;
constexpr short MAP_MOUSE_HOLE = 8;

constexpr short NUM_OF_MOUSE_HOLE = 10;

constexpr wchar_t* TEXT0 = L"确认请按回车";
constexpr wchar_t* TEXT1 = L"请确认上面这个框能正常在您的屏幕中显示";
constexpr wchar_t* TEXT2 = L"上下左右移动玩家(老鼠) 游戏目标 吃到食物后回到家里";
constexpr wchar_t* TEXT3 = L"玩家吃到了食物";
constexpr wchar_t* TEXT4 = L"玩家回到了家里 游戏结束 玩家获胜";
constexpr wchar_t* TEXT5 = L"猫抓住了玩家 游戏结束 玩家失败";
constexpr wchar_t* TEXT6 = L"玩家拾取了智能寻路系统";
constexpr wchar_t* TEXT7 = L"猫抓老鼠";
constexpr wchar_t* TEXT8 = L"开始游戏";
