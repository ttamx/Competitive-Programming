#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> vis(n,vector<int>(n));
    for(auto &v:vis)for(auto &x:v){
        char c;
        cin >> c;
        x=(c=='X');
    }
    int ans=0;
    queue<pair<int,int>> q;
    auto go=[&](int x,int y){
        if(x<0||y<0||vis[x][y])return;
        vis[x][y]=true;
        ans++;
        q.push({x,y});
    };
    go(n-1,n-1);
    while(!q.empty()){
        auto [x,y]=q.front();
        q.pop();
        go(x-1,y);
        go(x,y-1);
    }
    cout << ans;
}