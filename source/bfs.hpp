// coding=utf-8
// file: source/bfs.hpp

#include <queue>
#include <vector>
#include <algorithm>
#include "consts.hpp"
#include "structs.hpp"

std::vector<Pos> bfs(short map[WIDTH][HEIGHT], Pos start, Pos target) {
    std::vector<Pos> path;
    std::queue<Pos> q;

    bool visited[WIDTH][HEIGHT] = {false};
    q.push(start);
    visited[start.x][start.y] = true;
    
    Pos father[WIDTH][HEIGHT];
    for (short x=0;x<WIDTH;x++) {
        for (short y=0;y<HEIGHT;y++) {
            father[x][y] = Pos{-1, -1};
        }
    }

    while (!q.empty()) {
        Pos note = q.front();
        q.pop();

        if (note.x == target.x && note.y == target.y) {
            while (father[note.x][note.y].x != -1 || father[note.x][note.y].y != -1) {
                path.push_back(note);
                note = father[note.x][note.y];
            }
            path.push_back(note);
            std::reverse(path.begin(), path.end());
            return path;
        }

        Pos note1{note.x, note.y-1};
        if (note1.x >= 0 && note1.x < WIDTH && note1.y >= 0 && note1.y < HEIGHT &&
            !visited[note1.x][note1.y] && map[note1.x][note1.y] != MAP_WALL) {
            q.push(note1);
            visited[note1.x][note1.y] = true;
            father[note1.x][note1.y] = note;
        }
        Pos note2{note.x, note.y+1};
        if (note2.x >= 0 && note2.x < WIDTH && note2.y >= 0 && note2.y < HEIGHT &&
            !visited[note2.x][note2.y] && map[note2.x][note2.y] != MAP_WALL) {
            q.push(note2);
            visited[note2.x][note2.y] = true;
            father[note2.x][note2.y] = note;
        }
        Pos note3{note.x-1, note.y};
        if (note3.x >= 0 && note3.x < WIDTH && note3.y >= 0 && note3.y < HEIGHT &&
            !visited[note3.x][note3.y] && map[note3.x][note3.y] != MAP_WALL) {
            q.push(note3);
            visited[note3.x][note3.y] = true;
            father[note3.x][note3.y] = note;
        }
        Pos note4{note.x+1, note.y};
        if (note4.x >= 0 && note4.x < WIDTH && note4.y >= 0 && note4.y < HEIGHT &&
            !visited[note4.x][note4.y] && map[note4.x][note4.y] != MAP_WALL) {
            q.push(note4);
            visited[note4.x][note4.y] = true;
            father[note4.x][note4.y] = note;
        }
    }

    return path;
}
