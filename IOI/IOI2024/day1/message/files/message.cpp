#include <bits/stdc++.h>
#include "message.h"

using namespace std;

const int B=31;
const int P=16;

void send_message(vector<bool> M,vector<bool> C){
    int tail=M.back()^1;
    M.emplace_back(tail);
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(!C[i]){
            pos.emplace_back(i);
        }
    }
    vector<int> val(P);
    for(int i=0;i<P;i++){
        val[i]=(pos[(i+1)%P]-pos[i]+B)%B;
    }
    int cur=0;
    for(int i=0;i<B;i++){
        vector<bool> tmp(B);
        for(int j=0;j<P;j++){
            if(i<val[j]){
                if(i==val[j]-1){
                    tmp[pos[j]]=1;
                }
            }else{
                if(cur<M.size()){
                    tmp[pos[j]]=M[cur];
                    cur++;
                }else{
                    tmp[pos[j]]=tail;
                }
            }
        }
        send_packet(tmp);
    }
    while(cur<M.size()){
        vector<bool> tmp(B);
        for(auto x:pos){
            if(cur<M.size()){
                tmp[x]=M[cur];
                cur++;
            }else{
                tmp[x]=tail;
            }
        }
        send_packet(tmp);
    }
}

vector<bool> receive_message(vector<vector<bool>> R){
    vector<int> val(B);
    for(int i=B-1;i>=0;i--){
        for(int j=0;j<B;j++){
            if(R[i][j]){
                val[j]=i+1;
            }
        }
    }
    vector<int> nxt(B),deg(B);
    for(int i=0;i<B;i++){
        nxt[i]=(i+val[i])%B;
        deg[nxt[i]]++;
    }
    vector<bool> vis(B);
    queue<int> q;
    for(int i=0;i<B;i++){
        if(deg[i]==0){
            q.emplace(i);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        vis[u]=true;
        int v=nxt[u];
        deg[v]--;
        if(deg[v]==0){
            q.emplace(v);
        }
    }
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(vis[i]){
            continue;
        }
        vector<int> cyc;
        for(int u=i;!vis[u];u=nxt[u]){
            vis[u]=true;
            cyc.emplace_back(u);
        }
        if(cyc.size()==P){
            swap(cyc,pos);
        }
    }
    assert(!pos.empty());
    vector<bool> ans;
    for(int i=0;i<R.size();i++){
        for(int j=0;j<P;j++){
            if(i>=val[pos[j]]){
                ans.emplace_back(R[i][pos[j]]);
            }
        }
    }
    int tail=ans.back();
    while(ans.back()==tail){
        ans.pop_back();
    }
    return ans;
}
