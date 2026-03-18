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
    int n;
    cin >> n;
    vector<int> deg(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
        deg[u]++;
        deg[v]++;
    }
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<n;i++){
        pq.emplace(deg[i],i);
    }
    vector<int> ans(n,n-1);
    vector<int> q;
    vector<bool> vis(n);
    for(int i=0;i<n;i++){
        if(deg[i]==1){
            vis[i]=true;
            q.emplace_back(i);
        }
    }
    ans[1]=1;
    int cnt=0;
    int col=1;
    auto upd=[&](int i,int v){
        i=min(i,n-1);
        ans[i]=min(ans[i],v);
    };
    while(n-cnt>2){
        vector<int> nq;
        while(!pq.empty()){
            auto [d,i]=pq.top();
            if(d==deg[i])break;
            pq.pop();
        }
        col+=2;
        upd(cnt+(pq.empty()?0:pq.top().first),col-1);
        cnt+=q.size();
        upd(cnt+1,col);
        for(auto u:q){
            for(auto v:adj[u]){
                if(vis[v])continue;
                deg[v]--;
                if(deg[v]==1){
                    vis[v]=true;
                    nq.emplace_back(v);
                }else if(deg[v]>0){
                    pq.emplace(deg[v],v);
                }
            }
        }
        q=move(nq);
    }
    for(int i=n-2;i>=1;i--){
        ans[i]=min(ans[i],ans[i+1]);
    }
    for(int i=1;i<n;i++){
        cout << ans[i] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}