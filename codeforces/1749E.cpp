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
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    vector<vector<bool>> alive(n,vector<bool>(m,true));
    vector<vector<bool>> plant(n,vector<bool>(m,false));
    for(int i=0;i<n;i++){
        cin >> a[i];
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                plant[i][j]=true;
                if(i>0){
                    alive[i-1][j]=false;
                }
                if(i+1<n){
                    alive[i+1][j]=false;
                }
                if(j>0){
                    alive[i][j-1]=false;
                }
                if(j+1<m){
                    alive[i][j+1]=false;
                }
            }
        }
    }
    auto encode=[&](int i,int j){
        return i*m+j;
    };
    int s=n*m,t=n*m+1;
    vector<vector<pair<int,int>>> adj(t+1);
    auto link=[&](int u,int v,int w){
        adj[u].emplace_back(v,w);
    };
    for(int i=0;i<n;i++){
        if(alive[i][0]){
            link(s,encode(i,0),plant[i][0]?0:1);
        }
        if(alive[i][m-1]){
            link(encode(i,m-1),t,0);
        }
    }
    for(int i=0;i+1<n;i++){
        for(int j=0;j+1<m;j++){
            if(alive[i][j]&&alive[i+1][j+1]){
                link(encode(i,j),encode(i+1,j+1),plant[i+1][j+1]?0:1);
                link(encode(i+1,j+1),encode(i,j),plant[i][j]?0:1);
            }
        }
    }
    for(int i=0;i+1<n;i++){
        for(int j=1;j<m;j++){
            if(alive[i][j]&&alive[i+1][j-1]){
                link(encode(i,j),encode(i+1,j-1),plant[i+1][j-1]?0:1);
                link(encode(i+1,j-1),encode(i,j),plant[i][j]?0:1);
            }
        }
    }
    vector<int> par(t+1,-1),dist(t+1,INF);
    vector<bool> vis(t+1);
    deque<int> q{s};
    dist[s]=0;
    while(!q.empty()){
        int u=q.front();
        q.pop_front();
        if(vis[u])continue;
        vis[u]=true;
        int d=dist[u];
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                par[v]=u;
                if(w){
                    q.emplace_back(v);
                }else{
                    q.emplace_front(v);
                }
            }
        }
    }
    if(!vis[t]){
        cout << "NO\n";
        return;
    }
    for(int u=par[t];u!=s;u=par[u]){
        int i=u/m,j=u%m;
        a[i][j]='#';
    }
    cout << "YES\n";
    for(auto x:a){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}