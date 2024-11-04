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
    vector<int> a(n),b(m);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<ll> dp(n+1,LINF);
    dp[0]=0;
    for(int i=0;i<m;i++){
        deque<int> dq{0};
        ll sum=0;
        for(int l=0,r=0;r<n;r++){
            sum+=a[r];
            while(sum>b[i]){
                sum-=a[l];
                l++;
            }
            while(!dq.empty()&&dp[dq.back()]>dp[r+1]){
                dq.pop_back();
            }
            dq.emplace_back(r+1);
            while(!dq.empty()&&dq.front()<l){
                dq.pop_front();
            }
            if(!dq.empty()){
                dp[r+1]=min(dp[r+1],dp[dq.front()]+m-i-1);
            }
        }
    }
    cout << (dp[n]<LINF?dp[n]:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}