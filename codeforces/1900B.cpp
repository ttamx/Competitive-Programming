#include<bits/stdc++.h>

using namespace std;

const int N=305;

bool vis[N][N][N];
queue<tuple<int,int,int>> q;

void add(int i,int j,int k){
    if(vis[i][j][k]||i+j+k>300)return;
    vis[i][j][k]=true;
    q.emplace(i,j,k);
}

void runcase(){
    int a,b,c;
    cin >> a >> b >> c;
    cout << vis[a][b][c] << " " << vis[b][c][a] << " " << vis[c][a][b] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<=200;i++)add(i,0,0);
    while(!q.empty()){
        auto [i,j,k]=q.front();
        q.pop();
        if(i>0)add(i-1,j+1,k+1);
        if(j>0)add(i+1,j-1,k+1);
        if(k>0)add(i+1,j+1,k-1);
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}