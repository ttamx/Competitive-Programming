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
    priority_queue<tuple<int,ll,int>> pq;
    int n,m,p;
    cin >> n >> m >> p;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int h=(n+1)/2;
    pair<int,ll> ans(0,0LL);
    auto calc=[&](){
        int p=rng()%n;
        vector<int> pos;
        for(int j=0;j<m;j++){
            if(a[p][j]=='1'){
                pos.emplace_back(j);
            }
        }
        int k=pos.size();
        vector<int> dp(1<<k);
        for(int i=0;i<n;i++){
            int mask=0;
            for(int j=0;j<k;j++){
                if(a[i][pos[j]]=='1'){
                    mask|=1<<j;
                }
            }
            dp[mask]++;
        }
        for(int j=0;j<k;j++){
            for(int i=0;i<1<<k;i++){
                if(i>>j&1){
                    dp[i^(1<<j)]+=dp[i];
                }
            }
        }
        for(int i=0;i<1<<k;i++){
            if(dp[i]<h){
                continue;
            }
            ll mask=0;
            for(int j=0;j<k;j++){
                if(i>>j&1){
                    mask|=1LL<<pos[j];
                }
                ans=max(ans,make_pair(__builtin_popcount(i),mask));
            }
        }
    };
    for(int i=0;i<30;i++){
        calc();
    }
    for(int i=0;i<m;i++){
        cout << "01"[ans.second>>i&1];
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}