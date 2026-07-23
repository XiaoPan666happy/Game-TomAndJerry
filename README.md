# Game-TomAndJerry

一个windows命令提示符的猫抓老鼠小游戏

## 项目结构

`soure` 目录存放源代码

> `main.cpp` 项目主要逻辑以及程序的入口

> `bfs_thread.hpp` 此头文件提供`bfs_thread`函数用于单开后台线程运行广搜

> `cat.hpp` 此头文件提供`Cat`类封装了猫的行为

> `player.hpp` 此头文件提供`Player`类封装了玩家(老鼠)的行为

> `bfs.hpp` 此头文件提供了`bfs`函数用于执行广搜

> `consts.hpp` 此头文件定义的程序的常量

> `structs.hpp` 此头文件定义了程序的需要的结构体

> `input.hpp` 此头文件封装了部分的输入逻辑

> `output.hpp` 此头文件封装了部分的输出逻辑

`CompilerAndRun.ps1` 为重新编译并运行

`OnlyRun.ps1` 为运行上次编译生成的可执行文件

## 贡献指南

如果你想为这个项目做些什么请至 `Issues` 板块反馈

## 鸣谢与致谢

感谢 [龙腾猫跃](https://github.com/LTCatt)同志 PCL是世界上最好的Minecraft启动器!
