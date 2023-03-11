#include "rescuelib.h"
#include <vector>
#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <queue>
#include <stdio.h>

using namespace std;

class Point {
public:
    int r,c;
};

int cave_r,cave_c;    // row, col
int position_r,position_c;  // Eettan's position
int drop_count;
vector<pair<Point,Point>> walls;

vector<vector<int>> room,dist;  //-1 = wall, 0 = free, 1 = robot

void print(vector<vector<int>> &m) {
    int R = m.size();
    int C = m[0].size();
    for (int r = 0; r < R;r++) {
        for (int c = 0;c < C;c++) {
            printf("%3d",m[r][c]);
        }
        printf("\n");
    }
}

void get_size(int &uR, int &uC) {
    int n;
    cin >> cave_r >> cave_c;
    uR = cave_r;
    uC = cave_c;
    cin >> position_r >> position_c;
    cin >> n;
    walls.resize(n);
    for (int i = 0;i < n;i++) {
      cin >> walls[i].first.r >> walls[i].first.c;
      cin >> walls[i].second.r >> walls[i].second.c;
    }

    //build room
    room = vector<vector<int>>(cave_r+2, vector<int>(cave_c+2,0));
    dist = vector<vector<int>>(cave_r+2, vector<int>(cave_c+2,-1));
    for (int i = 0;i < cave_c+2;i++) {
      room[0][i] = -1;
      room[cave_r+1][i] = -1;
    }
    for (int i = 0;i < cave_r+2;i++) {
      room[i][0] = -1;
      room[i][cave_c+1] = -1;
    }
    for (int i = 0;i < n;i++) {
      int dr = walls[i].second.r - walls[i].first.r; dr = (dr == 0) ? 0 : dr / abs(dr);
      int dc = walls[i].second.c - walls[i].first.c; dc = (dc == 0) ? 0 : dc / abs(dc);
      int cr = walls[i].first.r;
      int cc = walls[i].first.c;
      while (cr != walls[i].second.r || cc != walls[i].second.c) {
        room[cr][cc] = -1;
        cr += dr;
        cc += dc;
      }
      room[cr][cc] = -1;

    }

    if (room[position_r][position_c] == -1) {
        cout << "INPUT ERROR: HUMAN IN WALL" << endl;
        exit(1);
    }
    room[position_r][position_c] = 1;

    //build distance
    dist[position_r][position_c] = 0;
    queue<Point> q;
    q.push( {position_r,position_c});
    vector<int> dr = {0,1,0,-1};
    vector<int> dc = {1,0,-1,0};
    while (q.empty() == false) {
        auto p = q.front();q.pop();
        int d = dist[p.r][p.c]+1;
        for (int j = 0;j < 4;j++) {
            int nr = p.r + dr[j];
            int nc = p.c + dc[j];
            if (room[nr][nc] == 0 && dist[nr][nc] == -1) {
                dist[nr][nc] = d;
                q.push({nr,nc});
            }
        }
    }
    //print(room);
    //print(dist);



    //reset drop count
    drop_count = 0;
}
int drop_robot(int r, int c) {
    if (r < 1 || r > cave_r || c < 1 || c > cave_c) {
        cout << "WRONG CALL TO drop_robot: r = " << r << " c = " << c << endl;
        exit(1);
    }
    drop_count++;
    return dist[r][c];
    return 0;
}

void answer(int r, int c) {
    if (r == position_r && c == position_c) {
        cout << "CORRECT" << endl;
        cout << "drop count = " << drop_count << endl;
    } else {
        cout << "WRONG ANSWER!! " << r << ' ' << c <<endl;
        cout << "drop count = " << drop_count << endl;
    }
    exit(0);
}
