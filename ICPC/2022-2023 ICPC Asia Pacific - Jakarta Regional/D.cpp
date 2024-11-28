#include<bits/stdc++.h>

using namespace std;

// using ll = long long;
using i128 = __int128_t;
using ll = i128;

const int N=1e5+5;
const ll INF=1e30;

int n,m;
int s,t;
ll a[N];
vector<pair<int,ll>> adj[N];
ll ds[N],dt[N];
ll ans=INF;

struct CovexHullTrick{
    struct Line{
        ll m,c;
        Line(ll _m,ll _c):m(_m),c(_c){}
        ll eval(ll x){
            return m*x+c;
        }
    };
    deque<Line> dq;
    bool bad(Line x,Line y,Line z){
        return i128(z.c-x.c)*(x.m-y.m)<=i128(y.c-x.c)*(x.m-z.m);
    }
    void insert(ll m,ll c){
        Line l(m,c);
        while(dq.size()>=2&&bad(dq.end()[-2],dq.back(),l)){
            dq.pop_back();
        }
        dq.emplace_back(l);
    }
    ll query(ll x){
        if(dq.empty())return -INF;
        while(dq.size()>=2&&dq[0].eval(x)<=dq[1].eval(x)){
            dq.pop_front();
        }
        return dq[0].eval(x);
    }
};

ll sq(ll x){
    return x*x;
}

void dijkstra(int st,ll* dist){
    for(int i=1;i<=n;i++){
        dist[i]=INF;
    }
    using P = pair<ll,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    dist[st]=0LL;
    pq.emplace(0LL,st);
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.emplace(d+w,v);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> t;
    for(int i=1;i<=n;i++){
        long long x;
        cin >> x;
        a[i] = x;
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        ll w=sq(a[u]-a[v]);
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    dijkstra(s,ds);
    dijkstra(t,dt);
    ans=ds[t] * 2ll;
    for(auto [i,_]:adj[t]){
        ans=min(ans,ds[i]*2);
    }
    for(auto [i,_]:adj[s]){
        ans=min(ans,dt[i]*2);
    }
    for(int i=1;i<=n;i++){
        vector<int> c;
        for(auto [x,_]:adj[i]){
            c.emplace_back(x);
        }
        sort(c.begin(),c.end(),[&](int i,int j){
            return a[i]<a[j];
        });
        {
            CovexHullTrick cht;
            for(auto j:c){
                ans=min(ans,sq(a[j])-cht.query(2ll*a[j])+2ll*ds[j]);
                cht.insert(a[j],-sq(a[j])-2ll*dt[j]);
            }
        }
        {
            CovexHullTrick cht;
            for(auto j:c){
                ans=min(ans,sq(a[j])-cht.query(2ll*a[j])+2ll*dt[j]);
                cht.insert(a[j],-sq(a[j])-2ll*ds[j]);
            }
        }
    }
    cout << fixed << setprecision(6);
    cout << (long double)ans/2.0 << "\n";
}