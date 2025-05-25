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
    int n,m,lim;
    cin >> n >> m >> lim;
    vector<vector<tuple<int,int,int>>> adj(n);
    int g[3]={};
    for(int i=0;i<m;i++){
        int u,v,w;
        char col;
        cin >> u >> v >> w >> col;
        u--,v--;
        int c=(col=='r'?0:(col=='g'?1:2));
        adj[u].emplace_back(v,w,c);
        adj[v].emplace_back(u,w,c);
        g[c]=gcd(g[c],w);
    }
    queue<pair<int,int>> q;
    vector<vector<bool>> vis(n,vector<bool>(8));
    q.emplace(0,0);
    vis[0][0]=true;
    while(!q.empty()){
        auto [u,s]=q.front();
        q.pop();
        for(auto [v,w,c]:adj[u]){
            int b=(w/g[c])&1;
            int ns=s^(b<<c);
            if(!vis[v][ns]){
                q.emplace(v,ns);
                vis[v][ns]=true;
            }
        }
    }
    int ans=INF;
    for(int s=0;s<8;s++){
        if(!vis[n-1][s]){
            continue;
        }
        int v[3]={};
        for(int i=0;i<3;i++){
            if(s>>i&1){
                v[i]=g[i];
            }
        }
        for(int i=0;i<3;i++){
            int j=(i+1)%3,k=(i+2)%3;
            int tj=g[j]/gcd(g[i],g[j]);
            int tk=g[k]/gcd(g[i],g[k]);
            int gt=gcd(tj,tk);
            vector<int> dj(gt,INF),dk(gt,INF);
            for(int t=0;t<tj;t++){
                dj[t%gt]=min((ll)dj[t%gt],(v[i]+v[j]+2LL*t*g[i])%(2*g[j]));
            }
            for(int t=0;t<tk;t++){
                dk[t%gt]=min((ll)dk[t%gt],(v[i]+v[k]+2LL*t*g[i])%(2*g[k]));
            }
            for(int t=0;t<gt;t++){
                ans=min(ans,max(dj[t],dk[t]));
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