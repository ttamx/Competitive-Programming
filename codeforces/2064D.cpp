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
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<int>> cur;
    vector<array<int,2>> ch;
    vector<bool> vis;
    auto new_node=[&](){
        cur.emplace_back(vector<int>{});
        ch.emplace_back(array<int,2>{-1,-1});
        vis.emplace_back(false);
        return cur.size()-1;
    };
    int root=new_node();
    for(int i=0;i<q;i++){
        int x;
        cin >> x;
        int u=root;
        for(int b=29;b>=0;b--){
            int c=x>>b&1;
            if(ch[u][c]==-1){
                ch[u][c]=new_node();
            }
            u=ch[u][c];
        }
        cur[u].emplace_back(i);
    }
    vector<int> ans(q,n);
    function<void(int,int)> dfs=[&](int u,int c){
        if(u==-1||vis[u])return;
        vis[u]=true;
        for(auto i:cur[u]){
            ans[i]=c;
        }
        for(auto v:ch[u]){
            dfs(v,c);
        }
    };
    reverse(a.begin(),a.end());
    int sum=0;
    for(int i=0;i<n;i++){
        int x=a[i];
        int u=root;
        for(int b=29;u!=-1&&b>=0;b--){
            int c=x>>b&1;
            if(c==1){
                dfs(ch[u][sum>>b&1],i);
            }
            u=ch[u][(x^sum)>>b&1];
        }
        sum^=x;
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}