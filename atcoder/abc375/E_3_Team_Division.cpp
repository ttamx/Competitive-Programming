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
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    int tot=accumulate(b.begin(),b.end(),0);
    if(tot%3!=0){
        cout << -1 << "\n";
        return;
    }
    tot/=3;
    vector<vector<int>> dp(tot+1,vector<int>(tot+1,INF));
    dp[0][0]=0;
    for(int i=0;i<n;i++){
        vector<vector<int>> ndp(tot+1,vector<int>(tot+1,INF));
        for(int j=0;j<=tot;j++){
            for(int k=0;k<=tot;k++){
                ndp[j][k]=min(ndp[j][k],dp[j][k]+(a[i]!=1));
            }
        }
        for(int j=0;j+b[i]<=tot;j++){
            for(int k=0;k<=tot;k++){
                ndp[j+b[i]][k]=min(ndp[j+b[i]][k],dp[j][k]+(a[i]!=2));
            }
        }
        for(int j=0;j<=tot;j++){
            for(int k=0;k+b[i]<=tot;k++){
                ndp[j][k+b[i]]=min(ndp[j][k+b[i]],dp[j][k]+(a[i]!=3));
            }
        }
        dp=move(ndp);
    }
    int ans=dp[tot][tot];
    cout << (ans<=n?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}