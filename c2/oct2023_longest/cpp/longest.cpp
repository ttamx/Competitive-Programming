#include "longest.h"
#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> longest(int N) {
    vector<pair<int,int>> ans;
    ans.emplace_back(0,0);
    ans.emplace_back(0,1);
    if(N==2)return ans;
    if(find(0,1,2)){
        ans.emplace_back(1,2);
    }else{
        ans.emplace_back(0,2);
    }
    for(int i=3;i<N;i++){
        auto [u,v]=ans.back();
        if(find(u,v,i)){
            if(find(u,i,v))u=i;
        }else{
            if(find(v,i,u))v=i;
        }
        ans.emplace_back(u,v);
    }
    return ans;
}