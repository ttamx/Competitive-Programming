#include <bits/stdc++.h>
#include "homework.h"

using namespace std;

typedef pair<int,int> p2;

int homework(int N, vector<vector<int>> HW, vector<vector<int>> B){
    vector<vector<int>> adj(N);
    vector<int> s(N),t(N),m(N),deg(N);
    for(int i=0;i<N;i++){
        s[i]=HW[i][0];
        t[i]=HW[i][1];
        m[i]=HW[i][2];
        deg[i]=HW[i][3];
        for(auto u:B[i])adj[u].emplace_back(i);
    }
    auto calc=[&](int i,int ct){
        return ((ct-1)/m[i]+1)*m[i];
    };
    priority_queue<p2,vector<p2>,greater<p2>> pq;
    for(int i=0;i<N;i++)if(deg[i]==0)pq.emplace(calc(i,s[i]),i);
    int ans=0;
    while(!pq.empty()){
        auto [ct,u]=pq.top();
        pq.pop();
        if(ct>t[u])continue;
        ans++;
        for(auto v:adj[u])if(--deg[v]==0)pq.emplace(calc(v,max(s[v],ct+1)),v);
    }
    return ans;
}