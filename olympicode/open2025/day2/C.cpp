#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;

int n;
int eu[N],ev[N];
ll ec[N];
int fa[N],sz[N],ans[N];
priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> event[N];
queue<int> q;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    ll tot=0;
    for(int i=1;i<n;i++){
        cin >> eu[i] >> ev[i] >> ec[i];
        if(ec[i]==1){
            q.emplace(i);
        }
        tot+=ec[i];
    }
    if(tot!=)
    for(int i=1;i<=n;i++){
        fa[i]=i;
        sz[i]=1;
    }
    int cur=0;
    while(!pq.empty()){
        auto [w,u,v,i]=pq.top();
        pq.pop();
        u=fp(u),v=fp(v);
        cerr << w << " " << u << " " << v << " : " << sz[u] << " " << sz[v] << "\n";
        if(1LL*sz[u]*sz[v]!=w){
            cout << "No\n";
            exit(0);
        }
        sz[u]+=sz[v];
        fa[v]=u;
        ans[i]=++cur;
    }
    for(int i=1;i<n;i++){
        cout << ans[i] << " \n"[i==n-1];
    }
}