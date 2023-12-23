#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;

int n,m;
vector<int> adj[N];
ll ans;
int l[N],r[N],l2[N],r2[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        l[i]=0,r[i]=n+1;
        for(auto j:adj[i]){
            if(j<i)l[i]=max(l[i],j);
            else r[i]=min(r[i],j);
        }
    }
    l[0]=0,r[0]=n+1;
    l[n+1]=0,r[n+1]=n+1;
    for(int i=1;i<=n;i++){
        l2[i]=0,r2[i]=n+1;
        for(auto j:adj[i]){
            if(j==l[i]||j==r[i])continue;
            if(j<i)l2[i]=max(l2[i],j);
            else r2[i]=min(r2[i],j);
        }
    }
    for(int i=1;i<=n;i++){
        ans+=1ll*(r[i]-i)*(i-l[i]);
        int res=r[l[i]];
        if(res==i)res=r2[l[i]];
        ans+=1ll*(l[i]-max(l2[i],l[l[i]]))*max(0,min(r[i],res)-i);
        res=l[r[i]];
        if(res==i)res=l2[r[i]];
        ans+=1ll*(min(r2[i],r[r[i]])-r[i])*max(0,i-max(l[i],res));
    }
    cout << ans;
}