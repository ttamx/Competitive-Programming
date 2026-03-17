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

const int N=3e5+5;

int n;
int lp[N];
vector<pair<int,int>> adj[N*2];
int dist[N*2];
int par[N*2];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++){
        if(lp[i])continue;
        lp[i]=i;
        for(int j=i;j<N;j+=i){
            if(!lp[j]){
                lp[j]=i;
            }
        }
    }
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        while(x>1){
            int p=lp[x];
            adj[i].emplace_back(n+p,1);
            adj[n+p].emplace_back(i,0);
            x/=p;
        }
    }
    int s,t;
    cin >> s >> t;
    for(int i=0;i<N*2;i++){
        dist[i]=INF;
    }
    deque<pair<int,int>> q;
    q.emplace_front(1,t);
    dist[t]=1;
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop_front();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                par[v]=u;
                if(w){
                    q.emplace_back(d+1,v);
                }else{
                    q.emplace_front(d,v);
                }
            }
        }
    }
    if(dist[s]<INF){
        cout << dist[s] << "\n";
        for(;s;s=par[s]){
            if(s<=n){
                cout << s << " ";
            }
        }
    }else{
        cout << -1;
    }
}