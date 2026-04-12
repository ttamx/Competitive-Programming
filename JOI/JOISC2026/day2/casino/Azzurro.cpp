#include "Azzurro.h"
#include<bits/stdc++.h>

using namespace std;

namespace {
    const int N=8;
    const int L=53;
    vector<int> table[N+1];
    void init(){
        if(!table[1].empty())return;
        for(int i=1;i<=N;i++){
            int n=1<<i;
            vector<vector<int>> adj(n);
            for(int j=0;j<n;j++){
                for(int x=3;x<n;x<<=1){
                    adj[j].emplace_back(j^x);
                }
            }
            vector<int> col(n,-1);
            function<void(int)> dfs=[&](int u){
                for(auto v:adj[u]){
                    if(col[v]==-1){
                        col[v]=col[u]^1;
                        dfs(v);
                    }else{
                        assert(col[u]!=col[v]);
                    }
                }
            };
            for(int j=0;j<n;j++){
                if(col[j]==-1){
                    col[j]=1;
                    dfs(j);
                }
            }
            for(int j=0;j<n;j++){
                if(col[j]){
                    table[i].emplace_back(j);
                }
            }
        }
    }
}

vector<vector<int>> Azzurro(int n,int k,string s){
    init();
    s.resize(L,'A');
    vector<vector<int>> res(n,vector<int>(n,0));
    vector<vector<pair<int,int>>> pos(2*n-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            pos[i+j].emplace_back(i,j);
        }
    }
    int p=0;
    for(int i=0;i<2*n-1;i++){
        int t=pos[i].size();
        int c=max(t-1,1);
        int cur=0;
        for(int j=0;j<c;j++){
            assert(p<s.size());
            if(s[p]=='B')cur|=1<<j;
            p++;
        }
        assert(cur<table[t].size());
        int v=table[t][cur];
        for(auto [x,y]:pos[i]){
            res[x][y]=v&1;
            v>>=1;
        }
    }
    return res;
}