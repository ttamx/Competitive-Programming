#include<bits/stdc++.h>

using namespace std;

int l,w,m;
int cnt[905];
int a[35][35];
int dp[35][35][35][35];
bool vis[35][35][35][35];
unordered_map<int,int> tmp;

int sol(int xl,int xr,int yl,int yr){
    if(vis[xl][xr][yl][yr])return dp[xl][xr][yl][yr];
    vis[xl][xr][yl][yr]=true;
    int ret=0;
    if(xl==xr){
        tmp.clear();
        for(int i=yl;i<=yr;++i)tmp[a[xl][i]]++;
        for(auto [i,v]:tmp)if(v==cnt[i])ret++;
    }else if(yl==yr){
        tmp.clear();
        for(int i=xl;i<=xr;++i)tmp[a[i][yl]]++;
        for(auto [i,v]:tmp)if(v==cnt[i])ret++;
    }else{
        ret=max(ret,sol(xl,xr-1,yl,yr)+sol(xr,xr,yl,yr));
        ret=max(ret,sol(xl,xl,yl,yr)+sol(xl+1,xr,yl,yr));
        ret=max(ret,sol(xl,xr,yl,yr-1)+sol(xl,xr,yr,yr));
        ret=max(ret,sol(xl,xr,yl,yl)+sol(xl,xr,yl+1,yr));
    }
    return dp[xl][xr][yl][yr]=ret; 
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> l >> w >> m;
    for(int i=1;i<=l;++i){
        for(int j=1;j<=w;++j){
            cin >> a[i][j];
            cnt[a[i][j]]++;
        }
    }
    cout << sol(1,l,1,w);
}