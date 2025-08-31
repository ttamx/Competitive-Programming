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

struct DSU{
    vector<int> p,sz;
    DSU(){}
    DSU(int n){init(n);}
    void init(int n){
        p.resize(n);
        iota(p.begin(),p.end(),0);
        sz.assign(n,1);
    }
    int find(int u){
        return p[u]==u?u:p[u]=find(p[u]);
    }
    bool same(int u,int v){
        return find(u)==find(v);
    }
    bool merge(int u,int v){
        u=find(u),v=find(v);
        if(u==v)return false;
        sz[u]+=sz[v];
        p[v]=u;
        return true;
    }
    int size(int u){
        return sz[find(u)];
    }
};

void runcase(){
    int n,m1,m2;
    cin >> n >> m1 >> m2;
    vector<pair<int,int>> e1(m1),e2(m2);
    for(auto &[u,v]:e1){
        cin >> u >> v;
        u--,v--;
    }
    for(auto &[u,v]:e2){
        cin >> u >> v;
        u--,v--;
    }
    DSU dsu1(n),dsu2(n);
    for(auto [u,v]:e2){
        dsu1.merge(u,v);
    }
    vector<vector<int>> comp(n);
    for(int i=0;i<n;i++){
        comp[dsu1.find(i)].emplace_back(i);
    }
    int ans=0;
    for(auto [u,v]:e1){
        if(dsu1.same(u,v)){
            dsu2.merge(u,v);
        }else{
            ans++;
        }
    }
    for(auto &c:comp){
        if(c.empty())continue;
        for(int i=1;i<c.size();i++){
            if(dsu2.merge(c[i-1],c[i])){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}