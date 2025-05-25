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

const int N=1e6+5;
const int K=30;

int n,k,q;
int nxt[N][K];
int dp[N];
string s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    cin >> s;
    for(int i=0;i<k;i++)nxt[n][i]=n;
    dp[n]=1;
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<k;j++)nxt[i][j]=nxt[i+1][j];
        nxt[i][s[i]-'a']=i;
        int mx=i;
        for(int j=0;j<k;j++)mx=max(mx,nxt[i][j]);
        dp[i]=dp[mx+1]+1;
    }
    cin >> q;
    while(q--){
        string t;
        cin >> t;
        int cur=0;
        bool ok=false;
        for(auto x:t){
            if(cur>=n){
                ok=true;
                break;
            }
            cur=nxt[cur][x-'a']+1;
        }
        cout << (ok?0:dp[cur]) << "\n";
    }
}