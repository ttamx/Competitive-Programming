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
    vector<pair<int,int>> edges(n-1);
    map<pair<int,int>,bool> link;
    for(auto &[u,v]:edges){
        cin >> u >> v;
        u--,v--;
        deg[u]++,deg[v]++;
        link[{u,v}]=link[{v,u}]=true;
    }
    int ans=0;
    for(auto [u,v]:edges){
        ans=max(ans,deg[u]+deg[v]-2);
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return deg[i]>deg[j];
    });
    for(int u=0;u<n;u++){
        int i=0;
        while(i<n&&(u==ord[i]||link.count(make_pair(u,ord[i])))){
            i++;
        }
        if(i<n){
            ans=max(ans,deg[u]+deg[ord[i]]-1);
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