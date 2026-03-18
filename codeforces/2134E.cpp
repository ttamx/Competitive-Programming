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

const bool LOCAL=false;

void runcase(){
    int n;
    cin >> n;
    vector<int> aa(n);
    if(LOCAL){
        for(auto &x:aa){
            cin >> x;
        }
    }
    auto ask_throw=[&](int x){
        cout << "throw " << x+1 << endl;
        if(LOCAL){
            int cur=x,cnt=0;
            while(cur<n){
                cur+=aa[cur];
                cnt++;
            }
            return cnt;
        }
        int v;
        cin >> v;
        return v;
    };
    vector<int> a(n);
    auto ask_swap=[&](int x){
        cout << "swap " << x+1 << endl;
        if(LOCAL){
            swap(aa[x],aa[x+1]);
        }
    };
    a[n-2]=3-ask_throw(n-2);
    ask_swap(n-2);
    a[n-1]=3-ask_throw(n-2);
    vector<int> dp(n+2);
    dp[n-1]=1;
    dp[n-2]=dp[n-2+a[n-1]]+1;
    for(int i=n-3;i>=0;i--){
        if(dp[i+1]!=dp[i+2]){
            int v=ask_throw(i);
            if(v==dp[i+1]+1){
                a[i]=1;
            }else if(v==dp[i+2]+1){
                a[i]=2;
            }else{
                assert(false);
            }
            dp[i]=v;
        }else{
            dp[i]=dp[i+1]+1;
        }
    }
    for(int i=0;i<n-2;i++){
        if(a[i])continue;
        assert(dp[i+1]==dp[i+2]);
        ask_swap(i);
        int v=ask_throw(i+1);
        if(v==dp[i+2]+1){
            a[i]=1;
        }else if(v==dp[i+3]+1){
            a[i]=2;
        }else{
            assert(false);
        }
        assert(a[i+1]!=0);
    }
    cout << "!";
    for(auto x:a){
        cout << " " << x;
    }
    cout << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}