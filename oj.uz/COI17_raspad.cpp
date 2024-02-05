#include<bits/stdc++.h>

using namespace std;

const int N=100005;
const int M=55;

int n,m;
string s[N];
long long ans;
bool vis[N][M];

pair<int,int> dfs(int i,int j){
    if(j==0||j==m-1)return {0,n-1};
    pair<int,int> res(i,i);
    vis[i][j]=true;
    for(int di=-1;di<=1;di++)for(int dj=-1;dj<=1;dj++){
        int ni=i+di,nj=j+dj;
        if(0<=ni&&ni<n&&0<=nj&&nj<m&&!vis[ni][nj]&&s[ni][nj]=='0'){
            auto [x,y]=dfs(ni,nj);
            res.first=min(res.first,x);
            res.second=max(res.second,y);
        }
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)cin >> s[i];
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(s[i][j]=='1')ans+=1LL*(i+1)*(n-i);
    for(int i=1;i<n;i++)for(int j=0;j<m;j++)if(s[i][j]=='1'&&s[i-1][j]=='1')ans-=1LL*i*(n-i);
    for(int i=0;i<n;i++)for(int j=1;j<m;j++)if(s[i][j]=='1'&&s[i][j-1]=='1')ans-=1LL*(i+1)*(n-i);
    for(int i=1;i<n;i++)for(int j=1;j<m;j++)if(s[i][j]=='1'&&s[i][j-1]=='1'&&s[i-1][j]=='1'&&s[i-1][j-1]=='1')ans+=1LL*i*(n-i);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)if(s[i][j]=='0'&&!vis[i][j]){
        auto [x,y]=dfs(i,j);
        ans+=1LL*x*(n-y-1);
    }
    cout << ans;
}