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

const db SCALE=1.0/(1LL<<32);

mt19937 _rng(chrono::steady_clock::now().time_since_epoch().count());

inline int rng(int n){return uniform_int_distribution<int>(0,n-1)(_rng);}

inline db rnd(){return _rng()*SCALE;}

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> edges(m);
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
    }
    vector<array<int,2>> adj(n,{-1,-1});
    vector<int> deg(n);
    vector<bool> used(m);
    int ans=0,score=0;
    for(int _t=0;_t<1000;_t++){
        for(int i=0;i<10000;i++){
            int id=rng(m);
            auto [u,v]=edges[id];
            int new_score=score;
            if(used[id]){
                new_score--;
            }else{
                new_score++;
                if(deg[u]==2)new_score--;
                if(deg[v]==2)new_score--;
            }
            ans=max(ans,new_score);
            if(new_score>=score||(i<1000&&(_rng()&3)==0)){
                if(used[id]){
                    used[id]=false;
                    deg[u]--,deg[v]--;
                    for(auto &x:adj[u]){
                        if(x==id){
                            x=-1;
                        }
                    }
                    for(auto &x:adj[v]){
                        if(x==id){
                            x=-1;
                        }
                    }
                }else{
                    used[id]=true;
                    if(deg[u]==2){
                        int &x=adj[u][_rng()&1];
                        used[x]=false;
                        x=-1;
                        deg[u]--;
                    }
                    if(deg[v]==2){
                        int &x=adj[v][_rng()&1];
                        used[x]=false;
                        x=-1;
                        deg[v]--;
                    }
                    deg[u]++;
                    deg[v]++;
                    for(auto &x:adj[u]){
                        if(x==-1){
                            x=id;
                            break;
                        }
                    }
                    for(auto &x:adj[v]){
                        if(x==-1){
                            x=id;
                            break;
                        }
                    }
                }
                score=new_score;
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