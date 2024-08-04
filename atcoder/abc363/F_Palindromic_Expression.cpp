#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

void runcase(){
    vector<tuple<ll,ll,ll>> val;
    auto add=[&](ll x){
        string s=to_string(x);
        for(auto c:s)if(c=='0')return;
        reverse(s.begin(),s.end());
        ll y=stoll(s);
        if(x<=y)val.emplace_back(x*y,x,y);
    };
    for(int i=2;i<=1000000;i++)add(i);
    sort(val.begin(),val.end());
    ll n;
    cin >> n;
    auto pal=[&](ll x){
        string s=to_string(x);
        for(auto c:s)if(c=='0')return false;
        string t=s;
        reverse(t.begin(),t.end());
        return s==t;
    };
    map<ll,pair<bool,tuple<ll,ll,ll>>> dp;
    function<bool(ll)> solve=[&](ll x){
        if(dp.count(x))return dp[x].first;
        if(pal(x)){
            dp[x]={true,{-1,-1,-1}};
            return true;
        }
        for(auto [d,a,b]:val){
            if(d>x)break;
            if(x%d==0){
                ll y=x/d;
                if(solve(y)){
                    dp[x].first=true;
                    dp[x].second={y,a,b};
                    break;
                }
            }
        }
        return dp[x].first;
    };
    if(solve(n)){
        vector<ll> l,r;
        while(true){
            auto [a,b,c]=dp[n].second;
            if(a==-1){
                break;
            }
            l.emplace_back(b);
            r.emplace_back(c);
            n=a;
        }
        reverse(r.begin(),r.end());
        for(auto x:l)cout << x << "*";
        cout << n;
        for(auto x:r)cout << "*" << x;
        return;
    }
    cout << -1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}