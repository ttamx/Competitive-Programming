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

const int N=4e5+5;
const int K=1<<20;

int n,q;
map<pair<int,int>,int> mpa,mpb;

struct DSU{
    int cnt=0;
    int fa[N],sz[N];
    stack<pair<int,int>> s;
    void init(){
        for(int i=1;i<=n;i++){
            fa[i]=i;
            sz[i]=1;
        }
    }
    int fp(int u){
        return u==fa[u]?u:fp(fa[u]);
    }
    void merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v){
            s.emplace(0,0);
            return;
        }
        if(sz[u]<sz[v]){
            swap(u,v);
        }
        fa[v]=u;
        sz[u]+=sz[v];
        s.emplace(u,v);
        cnt++;
    }
    void undo(){
        auto [u,v]=s.top();
        s.pop();
        if(u==0)return;
        fa[v]=v;
        sz[u]-=sz[v];
        cnt--;
    }
}dsua,dsub;

struct Update{
    DSU &dsu;
    int u,v;
    Update(DSU &_dsu,int _u,int _v):dsu(_dsu),u(_u),v(_v){}
    void apply(){
        dsu.merge(u,v);
    }
    void undo(){
        dsu.undo();
    }
};
vector<Update> t[K];

int ans[N];

void insert(int l,int r,int i,int x,int y,const Update &v){
    if(y<l||r<x)return;
    if(x<=l&&r<=y){
        t[i].emplace_back(v);
        return;
    }
    int m=(l+r)/2;
    insert(l,m,i*2,x,y,v);
    insert(m+1,r,i*2+1,x,y,v);
}

void insert(int x,int y,const Update &v){
    return insert(1,q,1,x,y,v);
}

void solve(int l,int r,int i){
    for(auto &&upd:t[i]){
        upd.apply();
    }
    if(l==r){
        ans[l]=dsub.cnt-dsua.cnt;
    }else{
        int m=(l+r)/2;
        solve(l,m,i*2);
        solve(m+1,r,i*2+1);
    }
    for(int j=t[i].size()-1;j>=0;j--){
        t[i][j].undo();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    dsua.init();
    dsub.init();
    for(int i=1;i<=q;i++){
        char op;
        int u,v;
        cin >> op >> u >> v;
        auto e=minmax(u,v);
        if(op=='A'){
            if(mpa.count(e)){
                insert(mpa[e],i-1,Update(dsua,u,v));
                insert(mpa[e],i-1,Update(dsub,u,v));
                mpa.erase(e);
            }else{
                mpa[e]=i;
            }
        }else{
            if(mpb.count(e)){
                insert(mpb[e],i-1,Update(dsub,u,v));
                mpb.erase(e);
            }else{
                mpb[e]=i;
            }
        }
    }
    for(auto &[e,i]:mpa){
        auto [u,v]=e;
        insert(i,q,Update(dsua,u,v));
        insert(i,q,Update(dsub,u,v));
    }
    for(auto &[e,i]:mpb){
        auto [u,v]=e;
        insert(i,q,Update(dsub,u,v));
    }
    solve(1,q,1);
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}