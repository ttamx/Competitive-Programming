#include <bits/stdc++.h>
#include "Alice.h"

using namespace std;

vector<pair<int,int>> Alice(){
    int n=89;
    long long x=setN(n);
    vector<pair<int,int>> res;
    for(int i=1;i<n;i++)res.emplace_back(x%i+1,i+1);
    return res;
}