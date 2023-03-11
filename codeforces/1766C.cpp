#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s[2];
    cin >> s[0];
    cin >> s[1];
    vector<vector<bool>> vis(2,vector<bool>(n));
    int cnt=0;
    for(int i=0;i<2;i++)for(int j=0;j<n;j++)if(s[i][j]=='W')vis[i][j]=true,cnt++;
    int cnt2=cnt;
    auto vis2=vis;
    function<void(int,int)> dfs=[&](int i,int j){
        if(vis[i][j])return;
        vis[i][j]=true;
        cnt++;
        if(!vis[i^1][j])return dfs(i^1,j);
        if(j+1<n&&!vis[i][j+1])return dfs(i,j+1);
    };
    dfs(0,0);
    if(cnt<2*n){
        cnt=cnt2;
        vis=vis2;
        dfs(1,0);
    }
    if(cnt==2*n)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}