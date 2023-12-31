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

using vpi = vector<pii>;

const int N=1e5+5;
const int Q=2e5+5;
const int K=450;

int n,m,q;
vi adj[N];
vpi dp[N];
int dist[N];
bool del[N],used[N];

vpi merge(const vpi &a,const vpi &b){
    vpi c;
    for(int i=0,j=0;sz(c)<K&&(i<sz(a)||j<sz(b));){
        if(j>=sz(b)||(i<sz(a)&&a[i]>b[j])){
            c.emplace_back(a[i]);
            used[a[i].second]=true;
            i++;
        }else{
            c.emplace_back(b[j]);
            used[b[j].second]=true;
            j++;
        }
        while(i<sz(a)&&used[a[i].second])i++;
        while(j<sz(b)&&used[b[j].second])j++;
    }
    for(auto [d,i]:c)used[i]=false;
    return c;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[v].emplace_back(u);
    }
    for(int u=1;u<=n;u++){
        dp[u]={{-1,u},{-INF,0}};
        for(auto v:adj[u])dp[u]=merge(dp[u],dp[v]);
        for(auto &[d,v]:dp[u])d++;
    }
    while(q--){
        int t,y;
        cin >> t >> y;
        vi c(y);
        for(auto &x:c){
            cin >> x;
            del[x]=true;
        }
        if(y<K){
            for(auto [d,u]:dp[t])if(!del[u]){
                cout << max(d,-1) << "\n";
                break;
            }
        }else{
            int ans=-1;
            for(int i=1;i<=t;i++)dist[i]=-INF;
            dist[t]=0;
            for(int u=t;u>=1;u--){
                if(!del[u])ans=max(ans,dist[u]);
                for(auto v:adj[u])dist[v]=max(dist[v],dist[u]+1);
            }
            cout << ans << "\n";
        }
        for(auto x:c)del[x]=false;
    }
}