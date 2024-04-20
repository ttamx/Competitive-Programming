#include<bits/stdc++.h>

using namespace std;

const int N=105;

int n,m;
vector<pair<int,int>> adj[N][N];
bool vis[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            char c;
            cin >> c;
            if(c=='B'||c=='R'){
                adj[i][j].emplace_back(i,j+1);
                adj[i][j+1].emplace_back(i,j);
            }
            if(c=='B'||c=='D'){
                adj[i][j].emplace_back(i+1,j);
                adj[i+1][j].emplace_back(i,j);
            }
        }
    }
    queue<tuple<int,int,int,int,int>> q;
    q.emplace(1,1,1,0,0);
    while(!q.empty()){
        auto [d,ui,uj,pi,pj]=q.front();
        q.pop();
        if(vis[ui][uj]){
            cout << d << "\n";
            cout << ui << " " << uj << "\n";
            exit(0);
        }
        vis[ui][uj]=true;
        for(auto [vi,vj]:adj[ui][uj]){
            if(vi==pi&&vj==pj)continue;
            q.emplace(d+1,vi,vj,ui,uj);
        }
    }
}