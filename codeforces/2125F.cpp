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

const string S="docker";

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    int m;
    cin >> m;
    int nn=n/6;
    vector<int> a(nn+1);
    for(int i=0;i<m;i++){
        int l,r;
        cin >> l >> r;
        if(l>nn)continue;
        a[l]++;
        if(r<nn)a[r+1]--;
    }
    int mx=0;
    for(int i=1;i<=nn;i++){
        a[i]+=a[i-1];
        mx=max(mx,a[i]);
    }
    int opt=0;
    for(int i=0;i<n;i++){
        if(s.substr(i,6)=="docker"){
            opt++;
        }
    }
    int opt1=-1,opt2=-1;
    for(int i=0;i<=nn;i++){
        if(a[i]==mx){
            if(i<=opt){
                opt1=i;
            }
            if(i>=opt&&opt2==-1){
                opt2=i;
            }
        }
    }
    auto calc=[&](int lambda){
        vector<pair<ll,int>> dp(n+1,{LINF,0});
        dp[0]={0,0};
        for(int i=0;i<n;i++){
            dp[i+1]=min(dp[i+1],dp[i]);
            if(i+6<=n){
                auto tmp=dp[i];
                for(int j=0;j<6;j++){
                    tmp.first+=(s[i+j]!=S[j]);
                }
                tmp.first+=lambda;
                tmp.second--;
                dp[i+6]=min(dp[i+6],tmp);
            }
        }
        return dp[n];
    };
    auto work=[&](ll k){
        ll l=-n-100,r=0;
        while(l<r){
            ll mid=l+(r-l+1)/2;
            auto [val,cnt]=calc(mid);
            if(-cnt>=k)l=mid;
            else r=mid-1;
        }
        return calc(l).first-l*k;
    };
    int ans=INF;
    if(opt1!=-1)ans=min(ans,opt-opt1);
    if(opt2!=-1)ans=min(ans,(int)work(opt2));
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}