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
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int f;
    cin >> f;
    vector<int> h(f);
    for(auto &x:h){
        cin >> x;
        x--;
    }
    int k;
    cin >> k;
    vector<int> p(k),id(n,-1),cnt(k);
    vector<bool> no_car(f);
    for(int i=0;i<k;i++){
        cin >> p[i];
        p[i]--;
        no_car[p[i]]=true;
        id[h[p[i]]]=i;
    }
    for(auto x:p)cnt[id[h[x]]]++;
    queue<pair<int,int>> q;
    vector dist(n,vector<int>(1<<k,-1));
    q.emplace(0,0);
    dist[0][0]=0;
    while(!q.empty()){
        auto [u,mask]=q.front();
        q.pop();
        int d=dist[u][mask];
        for(auto v:adj[u]){
            if(dist[v][mask]==-1){
                q.emplace(v,mask);
                dist[v][mask]=d+1;
            }
            if(id[v]==-1)continue;
            int mask2=mask|(1<<id[v]);
            if(dist[v][mask2]==-1){
                q.emplace(v,mask2);
                dist[v][mask2]=d+1;
            }
        }
    }
    vector<int> dp(1<<k,false);
    dp[0]=true;
    for(int i=0;i<f;i++){
        if(no_car[i])continue;
        vector<int> good(1<<k);
        int u=h[i];
        int d=dist[u][0];
        for(int mask=0;mask<1<<k;mask++){
            good[mask]=(dist[u][mask]==d);
        }
        for(int mask=(1<<k)-1;mask>0;mask--){
            for(int mask2=mask;mask2>0;mask2=(mask2-1)&mask){
                if(dp[mask^mask2]&&good[mask2]){
                    dp[mask]=true;
                }
            }
        }
    }
    int ans=0;
    for(int mask=0;mask<1<<k;mask++){
        if(!dp[mask])continue;
        int res=0;
        for(int i=0;i<k;i++){
            if(mask>>i&1){
                res+=cnt[i];
            }
        }
        ans=max(ans,res);
    }
    cout << k-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}