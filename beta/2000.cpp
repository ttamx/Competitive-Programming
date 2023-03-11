#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n;
int l[N],r[N];
bool ok=true;
int ans=0;
int mn[N],mx[N];

void dfs(int u=1,int lv=1){
    if(u==0)return;
    dfs(l[u],lv+1);
    dfs(r[u],lv+1);
    mx[u]=max(mx[l[u]],mx[r[u]])+1;
    mn[u]=min(mn[l[u]],mn[r[u]])+1;
}

void sol(int u=1){
    if(u==0)return;
    sol(l[u]);
    sol(r[u]);
    if(mn[l[u]]<mx[r[u]]){
        ans++;
        if(mn[r[u]]<mx[l[u]])ok=false;
    }
}

int main(){
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> l[i] >> r[i];
        l[i]=max(0,l[i]);
        r[i]=max(0,r[i]);
    }
    for(int i=1;i<=n;i++)mn[i]=n;
    dfs();
    sol();
    if(mx[1]-mn[1]<=1&&ok)cout << ans;
    else cout << -1;
}