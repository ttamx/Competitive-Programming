#include<bits/stdc++.h>

using namespace std;

const int N=405;

int n,m,q,cnt;
bool vis[N][N],blocked[N][N];
vector<pair<int,int>> qr;
vector<int> ans;

bool valid(int i,int j){
    return (i>=0&&i<n&&j>=0&&j<m&&!vis[i][j]&&!blocked[i][j]);
}

bool can(int i,int j){
    return (i<0||i>=n||j<0||j>=m||vis[i][j]);
}

void dfs(int i,int j){
    if(!valid(i,j))return;
    vis[i][j]=true;
    cnt++;
    dfs(i+1,j);
    dfs(i-1,j);
    dfs(i,j+1);
    dfs(i,j-1);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    qr.resize(q);
    for(auto &[x,y]:qr){
        cin >> x >> y;
        blocked[x][y]=true;
    }
    reverse(qr.begin(),qr.end());
    for(int i=0;i<n;i++)dfs(i,0),dfs(i,m-1);
    for(int i=0;i<m;i++)dfs(0,i),dfs(n-1,i);
    for(auto [x,y]:qr){
        ans.push_back(cnt);
        blocked[x][y]=false;
        if(can(x+1,y)||can(x-1,y)||can(x,y+1)||can(x,y-1))dfs(x,y);
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x << '\n';
}