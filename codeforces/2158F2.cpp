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

const ll LIM=1e18;

void runcase(){
    int n;
    cin >> n;
    int s=1;
    auto calc=[&](){
        int res=s*(s+1)/2;
        if(s%2==0){
            res-=s/2-1;
        }
        return res+1;
    };
    while(calc()<n){
        s++;
    }
    vector<vector<pair<int,int>>> adj(s);
    int buf=0;
    auto add_edge=[&](int u,int v){
        adj[u].emplace_back(v,buf);
        adj[v].emplace_back(u,buf);
        buf++;
    };
    for(int i=0;i<s;i++){
        for(int j=i;j<s;j++){
            if(s%2==0&&i%2==0&&j==i+1&&j<s-1)continue;
            add_edge(i,j);
        }
    }
    int cnt=0;
    for(int i=0;i<s;i++){
        if(adj[i].size()%2==1){
            cnt++;
        }
    }
    vector<bool> used(buf);
    vector<int> ans;
    function<void(int)> dfs=[&](int u){
        while(!adj[u].empty()){
            auto [v,i]=adj[u].back();
            adj[u].pop_back();
            if(used[i])continue;
            used[i]=true;
            dfs(v);
        }
        ans.emplace_back(u);
    };
    dfs(s-1);
    assert(ans.size()==calc());
    ans.resize(n);
    vector<ll> a(s,1);
    for(int i=0;i<s;i++){
        for(int j=0;j<i/10;j++){
            a[i]*=3;
        }
        for(int j=0;j<9-i/10;j++){
            a[i]*=5;
        }
        for(int j=0;j<i%10;j++){
            a[i]*=7;
        }
        for(int j=0;j<9-i%10;j++){
            a[i]*=11;
        }
        for(int j=0;j<i/10+i%10;j++){
            a[i]*=2;
        }
    }
    set<ll> st;
    for(int i=0;i+1<n;i++){
        ll g=gcd(a[ans[i]],a[ans[i+1]]);
        assert(!st.count(g));
        st.emplace(g);
    }
    for(auto x:ans){
        cout << a[x] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}