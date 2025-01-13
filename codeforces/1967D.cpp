#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(m),deg(m);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    for(auto &x:b){
        cin >> x;
        x--;
        deg[x]++;
    }
    vector<bool> vis(m);
    vector<int> q;
    for(int i=0;i<m;i++){
        if(deg[i]==0){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<q.size();i++){
        int u=q[i];
        vis[u]=true;
        if(--deg[b[u]]==0){
            q.emplace_back(b[u]);
        }
    }
    vector<int> dep(m),head(m);
    vector<vector<int>> adj(m);
    iota(head.begin(),head.end(),0);
    for(int i=q.size()-1;i>=0;i--){
        int u=q[i];
        head[u]=head[b[u]];
        dep[u]=dep[b[u]]+1;
        adj[b[u]].emplace_back(u);
    }
    vector<int> tin(m),tout(m);
    int timer=-1;
    auto dfs=[&](auto &&self,int u)->void {
        tin[u]=++timer;
        for(auto v:adj[u]){
            self(self,v);
        }
        tout[u]=timer;
    };
    for(int i=0;i<m;i++){
        if(!vis[i]){
            dfs(dfs,i);
        }
    }
    vector<int> group(m,-1),cyc(m),pos(m);
    for(int i=0;i<m;i++){
        if(vis[i])continue;
        int cnt=0;
        vector<int> ord;
        for(int j=i;!vis[j];j=b[j]){
            vis[j]=true;
            pos[j]=cnt++;
            ord.emplace_back(j);
        }
        for(auto j:ord){
            cyc[j]=cnt;
            group[j]=i;
        }
    }
    auto dist=[&](int u,int v){
        if(group[head[u]]!=group[head[v]])return INF;
        if(v!=head[v]&&!(tin[v]<=tin[u]&&tout[u]<=tout[v]))return INF;
        if(dep[u]<dep[v])return INF;
        int res=pos[head[v]]-pos[head[u]];
        if(res<0)res+=cyc[head[u]];
        return res+dep[u]-dep[v];
    };
    auto check=[&](int mid){
        int cur=0;
        for(auto x:a){
            while(cur<m&&dist(x,cur)>mid)cur++;
            if(cur==m)return false;
        }
        return true;
    };
    int l=0,r=m;
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    check(l);
    cout << (l<m?l:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}