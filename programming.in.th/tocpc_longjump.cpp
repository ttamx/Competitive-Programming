#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int n,m,w;
int xs,ys,xe,ye;
map<int,set<int>> sx,sy;
map<pair<int,int>,bool> vis;
queue<tuple<int,int,int>> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> w >> xs >> ys >> xe >> ye;
    for(int i=1;i<=w;i++){
        int x,y;
        cin >> x >> y;
        sx[y].emplace(x);
        sy[x].emplace(y);
    }
    vis[{xe,ye}]=true;
    q.emplace(0,xe,ye);
    while(!q.empty()){
        auto [d,x,y]=q.front();
        q.pop();
        if(x==xs&&y==ys)cout << d,exit(0);
        int xl,xr,yl,yr;
        auto it=sx[y].lower_bound(x);
        if(it==sx[y].begin())xl=1;
        else xl=*prev(it)+1;
        it=sx[y].upper_bound(x);
        if(it==sx[y].end())xr=n;
        else xr=*it-1;
        it=sy[x].lower_bound(y);
        if(it==sy[x].begin())yl=1;
        else yl=*prev(it)+1;
        it=sy[x].upper_bound(y);
        if(it==sy[x].end())yr=m;
        else yr=*it-1;
        if(!vis[{xl,y}]){
            vis[{xl,y}]=true;
            q.emplace(d+1,xl,y);
        }
        if(!vis[{xr,y}]){
            vis[{xr,y}]=true;
            q.emplace(d+1,xr,y);
        }
        if(!vis[{x,yl}]){
            vis[{x,yl}]=true;
            q.emplace(d+1,x,yl);
        }
        if(!vis[{x,yr}]){
            vis[{x,yr}]=true;
            q.emplace(d+1,x,yr);
        }
    }
    cout << -1;
}