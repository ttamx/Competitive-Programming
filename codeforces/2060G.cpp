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
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return min(a[i],b[i])<min(a[j],b[j]);
    });
    vector<array<array<bool,2>,2>> dp(n);
    dp[0][0][0]=true;
    dp[0][1][1]=true;
    for(int i=1;i<n;i++){
        int u=ord[i];
        int v=ord[i-1];
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                if(dp[i-1][j][k]){
                    for(int t=0;t<2;t++){
                        if(a[v]<a[u]&&b[v]<b[u]){
                            dp[i][t][k^t]=true;
                        }
                        swap(a[u],b[u]);
                    }
                }
            }
            swap(a[v],b[v]);
        }
    }
    cout << ((dp[n-1][0][0]||dp[n-1][1][0])?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}