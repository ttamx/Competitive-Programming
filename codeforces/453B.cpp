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

vector<int> prime{2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int m=prime.size();
    vector<int> mask(60);
    for(int i=1;i<60;i++){
        for(int j=0;j<m;j++){
            if(i%prime[j]==0){
                mask[i]|=1<<j;
            }
        }
    }
    vector<vector<pair<int,int>>> dp(n+1,vector<pair<int,int>>(1<<m,{INF,-1}));
    fill(dp[0].begin(),dp[0].end(),make_pair(0,-1));
    for(int i=0;i<n;i++){
        for(int x=1;x<=a[i]*2-1;x++){
            int mask2=(~mask[x])&((1<<m)-1);
            for(int j=mask2;;j=(j-1)&mask2){
                dp[i+1][j|mask[x]]=min(dp[i+1][j|mask[x]],make_pair(dp[i][j].first+abs(a[i]-x),x));
                if(j==0)break;
            }
        }
    }
    vector<int> ans;
    for(int i=n,j=(1<<m)-1;i>0;i--){
        ans.emplace_back(dp[i][j].second);
        j^=mask[dp[i][j].second];
    }
    reverse(ans.begin(),ans.end());
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}