#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    queue<pair<int,int>> q;
    vector<bool> vis(max(n,m*2)+1);
    q.emplace(n,0);
    vis[n]=true;
    while(!q.empty()){
        auto [u,d]=q.front();
        q.pop();
        if(u==m){
            cout << d << "\n";
            exit(0);
        }
        if(u>1&&!vis[u-1]){
            q.emplace(u-1,d+1);
            vis[u-1]=true;
        }
        if(u<m&&!vis[u*2]){
            q.emplace(u*2,d+1);
            vis[u*2]=true;
        }
    }
    assert(false);
}