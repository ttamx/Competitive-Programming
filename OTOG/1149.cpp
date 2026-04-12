#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<int,int,int>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> dist(n,vector<int>(m,-1));
    queue<pair<int,int>> q;
    auto ok=[&](int i,int j){
        if(i<0||i>=n||j<0||j>=m)return false;
        return true;
    };
    auto go=[&](int i,int j,int d){
        if(i<0||i>=n||j<0||j>=m||a[i][j]=='#'||dist[i][j]!=-1)return;
        dist[i][j]=d;
        q.emplace(i,j);
    };
    go(0,0,0);
    string dir="ULRD";
    int dx[]={-1,0,0,1};
    int dy[]={0,-1,1,0};
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        for(int t=0;t<4;t++){
            int ii=i+dx[t],jj=j+dy[t];
            if(ok(ii,jj)&&a[ii][jj]==dir[t]){
                ii+=dx[t],jj+=dy[t];
                if(ok(ii,jj)&&a[ii][jj]=='#'){
                    ii-=dx[t],jj-=dy[t];
                }
            }
            go(ii,jj,dist[i][j]+1);
        }
    }
    cout << dist[n-1][m-1] << "\n";
}