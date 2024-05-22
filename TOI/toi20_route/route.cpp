#include <bits/stdc++.h>
#include "route.h"

using namespace std;

vector<pair<int,int>> route(int n,vector<int> w){
    int m=w.size();
    vector<int> ord(m);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return w[i]<w[j];
    });
    vector<pair<int,int>> ans(m);
    int cur=1,aux=2;
    for(auto i:ord){
        if(m>=n&&aux<cur){
            ans[i]={aux++,cur};
            m--;
        }else{
            ans[i]={1,++cur};
            aux=2;
        }
    }
    return ans;
}