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
    int n,x,y,s;
    cin >> n >> x >> y >> s;
    int z=x%y;
    if(s<1LL*z*(n-1)+x){
        cout << "NO\n";
        return;
    }
    s-=z*n;
    x-=z;
    vector<int> dp(s+1,INF);
    vector<int> par(s+1,-1);
    dp[0]=0;
    for(int i=1;i<=s;i++){
        int p=i;
        for(int j=1;p>=0;j++){
            if(dp[p]+j<dp[i]){
                dp[i]=dp[p]+j;
                par[i]=p;
            }
            p-=y*j;
        }
    }
    int sum=x;
    for(int i=1;sum<=s;i++){
        if(i+dp[s-sum]<=n){
            cout << "YES\n";
            vector<int> ans;
            for(int j=0;j<i;j++){
                ans.emplace_back(x+j*y);
            }
            for(int u=s-sum;u!=0;u=par[u]){
                int dif=dp[u]-dp[par[u]];
                for(int j=0;j<dif;j++){
                    ans.emplace_back(j*y);
                }
            }
            while(ans.size()<n){
                ans.emplace_back(0);
            }
            for(auto x:ans){
                cout << x+z << " ";
            }
            cout << "\n";
            return;
        }
        sum+=x+y*i;
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}