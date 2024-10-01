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
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<tuple<int,int,int,int>>> lst(n);
    for(int i=0;i<m;i++){
        int e,t,p;
        cin >> e >> t >> p;
        e--;
        lst[e].emplace_back(e,t,p,i);
    }
    vector<int> ans;
    ll cur=0;
    for(int i=0;i<n;i++){
        int m=lst[i].size();
        vector<array<tuple<ll,int,int,int>,101>> dp(m+1);
        for(int j=0;j<=100;j++){
            dp[0][j]={LINF,-1,-1,-1};
        }
        get<0>(dp[0][0])=0LL;
        for(int j=0;j<m;j++){
            auto [e,t,p,id]=lst[i][j];
            dp[j+1]=dp[j];
            for(int k=0;k<=100;k++){
                int x=min(k+p,100);
                dp[j+1][x]=min(dp[j+1][x],make_tuple(get<0>(dp[j][k])+t,j,k,id));
            }
        }
        cur+=get<0>(dp[m][100]);
        if(cur>a[i]){
            cout << -1 << "\n";
            return;
        }
        for(int j=m,k=100;k>0;){
            auto [_,nj,nk,x]=dp[j][k];
            ans.emplace_back(x);
            j=nj,k=nk;
        }
    }
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}