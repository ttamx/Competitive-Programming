#include "Bruno.h"
#include <bits/stdc++.h>

using namespace std;

int Bruno(int n,int m,vector<int> c){
    int v=c.back();
    c.pop_back();
    if(c.empty())return v?n:0;
    return c[0]==0?n-c.size():c.size();
}