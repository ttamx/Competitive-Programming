#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

struct DSU{
    vi p,sz;
    DSU(){}
    DSU(int n){
        init(n);
    }
    void init(int n){
        p.resize(n);
        iota(all(p),0);
        sz.assign(n,1);
    }
    int fp(int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    }
    bool merge(int u,int v){
        u=fp(u),v=fp(v);
        if(u==v)return false;
        if(sz[u]<sz[v])swap(u,v);
        p[v]=u;
        sz[u]+=sz[v];
        return true;
    }
    bool same(int u,int v){
        return fp(u)==fp(v);
    }
    int size(int u){
        return sz[fp(u)];
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,c;
    cin >> n >> c;
    vector<tuple<int,int,int>> edge;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int w;
            cin >> w;
            if(i<j&&w)edge.emplace_back(w,i,j);
        }
    }
    sort(edge.begin(),edge.end());
    int ans=INF;
    for(int mask=1;mask<1<<n;mask++){
        DSU dsu(n);
        int cnt=0,res=0;
        for(auto [w,u,v]:edge){
            if(((mask>>u&1)||(mask>>v&1))&&dsu.merge(u,v)){
                cnt++;
                res+=w;
            }
        }
        if(cnt==n-1)ans=min(ans,res+c*__builtin_popcount(mask));
    }
    cout << ans;
}