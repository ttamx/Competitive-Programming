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
    string s;
    cin >> s;
    int n;
    cin >> n;
    vector dp(n,vector<vector<pair<int,int>>>(11,vector<pair<int,int>>(11,{-1,-1})));
    for(int i=1;i<=10;i++){
        if(s[i-1]=='1'){
            dp[0][i][i]={0,0};
        }
    }
    for(int i=1;i<n;i++){
        for(int j=1;j<=10;j++){
            if(s[j-1]=='0')continue;
            for(int k=1;k<=10;k++){
                if(s[k-1]=='0')continue;
                if(j==k)continue;
                for(int d=0;d<=10;d++){
                    if(dp[i-1][k][d].first!=-1&&j>d){
                        dp[i][j][j-d]={k,d};
                    }
                }
            }
        }
    }
    int x=-1,y=-1;
    for(int i=1;i<=10;i++){
        for(int j=1;j<=10;j++){
            if(dp[n-1][i][j].first!=-1){
                x=i,y=j;
                break;
            }
        }
    }
    if(x==-1){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    vector<int> ans;
    for(int i=n-1;i>=0;i--){
        ans.emplace_back(x);
        tie(x,y)=dp[i][x][y];
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