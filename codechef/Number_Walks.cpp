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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<map<int,int>> id(m+1);
    for(int i=0;i<n;i++)id[0][i];
    for(int i=0;i<n;i++){
        id[a[i]][i];
        id[a[i]-1][i];
    }
    int nn=0;
    for(auto &v:id)for(auto &[_,x]:v)x=nn++;
    vector<vector<pair<int,int>>> adj(nn);
    for(auto &v:id){
        int p=-1,pi=-1;
        for(auto &[xi,x]:v){
            if(p!=-1){
                adj[x].emplace_back(p,xi-pi);
                adj[p].emplace_back(x,xi-pi);
            }
            p=x;
            pi=xi;
        }
    }
    for(int i=0;i<n;i++){
        adj[id[a[i]][i]].emplace_back(id[a[i]-1][i],0);
    }
    using P = pair<ll,int>;
    vector<ll> dist(nn,LINF);
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=0;i<n;i++){
        if(a[i]==m){
            int x=id[m][i];
            pq.emplace(dist[x]=0,x);
        }
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(d>dist[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                pq.emplace(dist[v]=d+w,v);
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << dist[i] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}