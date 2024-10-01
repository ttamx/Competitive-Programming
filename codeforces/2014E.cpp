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

void runcase(){
    int n,m,h;
    cin >> n >> m >> h;
    vector<bool> horse(n);
    for(int i=0;i<h;i++){
        int x;
        cin >> x;
        x--;
        horse[x]=true;
    }
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    auto dijkstra=[&](int s){
        vector<array<ll,2>> dist(n,{LINF,LINF});
        using T = tuple<ll,int,int>;
        priority_queue<T,vector<T>,greater<T>> pq;
        dist[s][0]=0;
        pq.emplace(0,s,0);
        while(!pq.empty()){
            auto [d,u,i]=pq.top();
            pq.pop();
            if(d>dist[u][i])continue;
            if(i==0&&horse[u]&&d<dist[u][1]){
                dist[u][1]=d;
                pq.emplace(d,u,1);
            }
            for(auto [v,w]:adj[u]){
                if(i==1)w/=2;
                if(d+w<dist[v][i]){
                    dist[v][i]=d+w;
                    pq.emplace(d+w,v,i);
                }
            }
        }
        for(int i=0;i<n;i++){
            dist[i][1]=min(dist[i][0],dist[i][1]);
        }
        return dist;
    };
    auto dist1=dijkstra(0);
    auto dist2=dijkstra(n-1);
    ll ans=LINF;
    for(int i=0;i<n;i++){
        ans=min(ans,max(dist1[i][1],dist2[i][1]));
    }
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}