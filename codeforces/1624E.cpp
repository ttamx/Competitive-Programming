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
    string s;
    vector<string> a(n);
    for(auto &x:a)cin >> x;
    cin >> s;
    map<string,tuple<int,int,int>> mp;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(j+1<m)mp[a[i].substr(j,2)]={j,j+1,i};
            if(j+2<m)mp[a[i].substr(j,3)]={j,j+2,i};
        }
    }
    vector<bool> dp(m+1);
    vector<int> pre(m+1,-1);
    dp[0]=true;
    for(int i=0;i<m;i++){
        if(!dp[i])continue;
        if(i+1<m&&mp.count(s.substr(i,2))){
            dp[i+2]=true;
            pre[i+2]=i;
        }
        if(i+2<m&&mp.count(s.substr(i,3))){
            dp[i+3]=true;
            pre[i+3]=i;
        }
    }
    if(!dp[m]){
        cout << -1 << "\n";
    }else{
        vector<tuple<int,int,int>> ans;
        for(int i=m;i>0;i=pre[i]){
            ans.emplace_back(mp[s.substr(pre[i],i-pre[i])]);
        }
        reverse(ans.begin(),ans.end());
        cout << ans.size() << "\n";
        for(auto [l,r,i]:ans){
            cout << l+1 << " " << r+1 << " " << i+1 << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}