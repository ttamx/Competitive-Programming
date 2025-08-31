#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;
const int INF=INT_MAX/2;

int n,rt,q;
int a[N];
vector<int> adj[N];
int dep[N],tin[N],tout[N];
int timer;
int ans;

struct Segtree{
    vector<pair<int,int>> t[K];
    void update(int l,int r,int i,int x,int dep,int val){
        if(x<l||r<x)return;
        if(!t[i].empty()){
            if(t[i].back().first==dep){
                t[i].back().second=min(t[i].back().second,val);
            }else if(val<t[i].back().second){
                t[i].emplace_back(dep,val);
            }
        }else{
            t[i].emplace_back(dep,val);
        }
        if(l==r)return;
        int m=(l+r)/2;
        update(l,m,i*2,x,dep,val);
        update(m+1,r,i*2+1,x,dep,val);
    }
    void update(int x,int dep,int val){
        update(1,n,1,x,dep,val);
    }
    int query(int l,int r,int i,int x,int y,int dep){
        if(y<l||r<x)return INF;
        if(x<=l&&r<=y){
            auto it=lower_bound(t[i].begin(),t[i].end(),make_pair(dep+1,0));
            return it==t[i].begin()?INF:prev(it)->second;
        }
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y,dep),query(m+1,r,i*2+1,x,y,dep));
    }
    int query(int x,int y,int dep){
        return query(1,n,1,x,y,dep);
    }
}seg;

void dfs(int u,int p){
    tin[u]=++timer;
    dep[u]=dep[p]+1;
    int hv=0;
    for(auto v:adj[u]){
        if(v==p)continue;
        dfs(v,u);
    }
    tout[u]=timer;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> rt;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    dfs(rt,0);
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),1);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return dep[i]<dep[j];
    });
    for(auto u:ord){
        seg.update(tin[u],dep[u],a[u]);
    }
    cin >> q;
    while(q--){
        int x,k;
        cin >> x >> k;
        x=(x+ans)%n+1;
        k=(k+ans)%n+1;
        ans=seg.query(tin[x],tout[x],dep[x]+k-1);
        cout << ans << "\n";
    }
}