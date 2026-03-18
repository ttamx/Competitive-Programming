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
    int nn=(n+2)*2*(m+1);
    vector<vector<pair<int,int>>> adj(nn);
    auto link=[&](int u,int v,int w){
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    };
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            int up=i*2*(m+1)+j;
            int dn=(i+1)*2*(m+1)+j;
            int le=(i*2+1)*(m+1)+j;
            int ri=(i*2+1)*(m+1)+j+1;
            link(le,ri,s[j]!='A');
            link(up,dn,s[j]!='A');
            link(le,dn,s[j]!='B');
            link(ri,up,s[j]!='B');
            link(le,up,s[j]!='C');
            link(ri,dn,s[j]!='C');
        }
    }
    int st=m+1,ed=n*2*(m+1)-1;
    vector<int> dp(nn,INF);
    deque<pair<int,int>> q;
    dp[st]=0;
    q.emplace_back(0,st);
    while(!q.empty()){
        auto [d,u]=q.front();
        q.pop_front();
        if(u==ed){
            cout << d << "\n";
            return;
        }
        if(d>dp[u])continue;
        for(auto [v,w]:adj[u]){
            if(d+w<dp[v]){
                dp[v]=d+w;
                if(w){
                    q.emplace_back(dp[v],v);
                }else{
                    q.emplace_front(dp[v],v);
                }
            }

        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}