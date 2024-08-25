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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

using ull = uint64_t;

struct Fenwick{
    int n;
    vector<ull> t;
    Fenwick(int n):n(n),t(n+1){}
    void update(int x,ull v){
        for(int i=x+1;i<=n;i+=i&-i){
            t[i]^=v;
        }
    }
    ull query(int x){
        ull res=0;
        for(int i=x+1;i;i-=i&-i){
            res^=t[i];
        }
        return res;
    }
    ull query(int l,int r){
        return query(r)^query(l-1);
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> p(n,-1),lv(n),a(n);
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        cin >> p[i];
        p[i]--;
        lv[i]=lv[p[i]]+1;
        adj[p[i]].emplace_back(i);
    }
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> pre,sub(n);
    vector<ull> val(n);
    vector<ull> hsh(n),arr(n);
    for(auto &x:hsh)x=rng();
    for(int i=0;i<n;i++)arr[i]=hsh[a[i]];
    auto pref=hsh;
    for(int i=1;i<n;i++)pref[i]^=pref[i-1];
    function<int(int,int)> dfs=[&](int u,int p){
        int x=pre.size();
        pre.emplace_back(p);
        sub[x]=1;
        val[u]=hsh[u];
        for(auto v:adj[u]){
            sub[x]+=dfs(v,x);
            val[u]^=val[v];
        }
        return sub[x];
    };
    dfs(0,-1);
    Fenwick f(n);
    for(int i=0;i<n;i++){
        f.update(i,arr[i]);
    }
    vector<int> ok(n);
    int cur=0;
    auto update=[&](int i){
        for(;i!=-1;i=pre[i]){
            cur-=ok[i];
            ok[i]=(f.query(i,i+sub[i]-1)==val[a[i]]);
            cur+=ok[i];
        }
    };
    for(int i=0;i<n;i++){
        update(i);
    }
    while(q--){
        int x,y;
        cin >> x >> y;
        x--,y--;
        f.update(x,arr[x]^arr[y]);
        f.update(y,arr[x]^arr[y]);
        swap(a[x],a[y]);
        swap(arr[x],arr[y]);
        update(x);
        update(y);
        cout << (cur==n?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}