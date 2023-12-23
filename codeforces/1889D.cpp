#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
stack<int> st[N];
int dp[N],pos[N],disc[N];
int timer;

int dfs(int u){
    if(dp[u])return dp[u];
    if(st[u].empty())return u;
    if(disc[u]){
        pos[timer+1]=0;
        while(pos[timer+1]!=u){
            int v=pos[timer--];
            st[v].pop();
            disc[v]=0;
        }
        return dfs(u);
    }
    disc[u]=++timer;
    pos[timer]=u;
    return dfs(st[u].top());
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int k;
        cin >> k;
        while(k--){
            int x;
            cin >> x;
            st[i].emplace(x);
        }
    }
    for(int i=1;i<=n;i++){
        int res=dfs(i);
        while(timer>0)dp[pos[timer--]]=res;
        cout << res << " \n"[i==n];
    }
}