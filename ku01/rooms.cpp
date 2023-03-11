#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int r,c;
    cin >> r >> c;
    vector<vector<char>> g(r);
    for(auto &v:g)v.resize(c);
    vector<vector<bool>> vis(r);
    for(auto &v:vis)v.resize(c);
    queue<pair<int,int>> q,w;
    auto go=[&](int x,int y){
        if(x>=0&&y>=0&&x<r&&y<c&&!vis[x][y]){
            q.push({x,y});
            vis[x][y]=true;
        };
    };
    for(int i=0;i<r;i++)for(int j=0;j<c;j++){
        cin >> g[i][j];
        if(g[i][j]=='A')go(i,j);
        if(g[i][j]=='W')w.push({i,j});
        vis[i][j]=(g[i][j]=='#');
    }
    int ans=0;
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        if(g[x][y]=='*')ans++;
        if(g[x][y]=='W')while(!w.empty()){
            auto [i,j]=w.front();
            w.pop();
            go(i,j);
            g[i][j]='.';
        }
        go(x-1,y);
        go(x,y-1);
        go(x+1,y);
        go(x,y+1);
    }
    cout << ans;
}