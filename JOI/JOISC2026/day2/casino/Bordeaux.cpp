#include "Bordeaux.h"
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
    int find(int i,int v){
        auto it=find(table[i].begin(),table[i].end(),v);
        return it!=table[i].end()?it-table[i].begin():-1;
    }
}

string Bordeaux(int n,int k,vector<vector<int>> a) {
    init();
    string s="";
    vector<vector<pair<int,int>>> pos(2*n-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            pos[i+j].emplace_back(i,j);
        }
    }
    int p=0,d=1;
    for(int i=0;i<2*n-1;i++){
        if(i==n)d=-1;
        int t=pos[i].size();
        int c=max(t-1,1);
        int cur=0;
        for(int j=0;j<t;j++){
            auto [x,y]=pos[i][j];
            cur|=a[x][y]<<j;
        }
        int v=find(t,cur^(1<<p));
        if(v==-1&&p+d>=0){
            p+=d;
            v=find(t,cur^(1<<p));
        }
        assert(v!=-1);
        for(int j=0;j<c;j++){
            s.push_back('A'+(v>>j&1));
        }
    }
    s.resize(k);
	return s;
}