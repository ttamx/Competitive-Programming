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

ll gcd(ll a,ll b,ll &x,ll &y){
    if(!b)return x=1,y=0,a;
    ll u,v,t=gcd(b,a%b,u,v);
    x=v,y=u-v*(a/b);
    return t;
}

void runcase(){
    int n,m,h;
    cin >> n >> m >> h;
    vl l(n),s(n);
    for(auto &x:l)cin >> x;
    for(auto &x:s)cin >> x;
    vector<vector<tuple<int,ll,ll>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(s[u]<s[v])swap(u,v);
        ll dif=s[u]-s[v];
        ll tar=l[v]-l[u];
        ll x,y;
        ll g=gcd(dif,h,x,y);
        if(tar%g)continue;
        ll mul=tar/g;
        x*=mul;
        ll mod=h/gcd(dif,h);
        if(x<0)x+=(-x)/mod*mod+mod;
        x%=mod;
        adj[u].emplace_back(v,x,mod);
        adj[v].emplace_back(u,x,mod);
    }
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    vl dist(n,LINF);
    dist[0]=0;
    pq.emplace(0,0);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        if(u==n-1)return void(cout << d << "\n");
        for(auto [v,x,mod]:adj[u]){
            ll nd=d+(x+mod-d%mod)%mod+1;
            if(dist[v]<=nd)continue;
            dist[v]=nd;
            pq.emplace(nd,v);
        }
    }
    cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}