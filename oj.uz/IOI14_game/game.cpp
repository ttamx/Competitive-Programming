#include "game.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1505;

int n;
int cnt[N];

void initialize(int _n) {
    n=_n;
}

int hasEdge(int u, int v) {
    if(u<v)swap(u,v);
    return ++cnt[u]==u;
}