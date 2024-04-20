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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vl a(n),b;
    for(auto &x:a){
        cin >> x;
        for(int i=1;i<=n;i++)b.emplace_back(x*i);
    }
    sort(all(b));
    b.erase(unique(all(b)),b.end());
    int m=sz(b);
    vector<vi> adj(m);
    for(int i=0;i<n;i++){
        for(int j=1;j<=n;j++){
            int id=lower_bound(all(b),a[i]*j)-b.begin();
            adj[id].emplace_back(i);
        }
    }
    vector<bool> vis(m);
    vi match(n,-1);
    function<bool(int)> khun=[&](int u){
        if(vis[u])return false;
        vis[u]=true;
        for(auto v:adj[u])if(match[v]==-1||khun(match[v]))return match[v]=u,true;
        return false;
    };
    ll ans=0;
    for(int i=0;i<m;i++){
        if(khun(i)){
            ans+=b[i];
            vis.assign(n,false);
        }
    }
    cout << ans;
}