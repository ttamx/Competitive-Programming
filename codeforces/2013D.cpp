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
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    reverse(a.begin(),a.end());
    stack<pair<ll,ll>> s;
    for(auto x:a){
        ll cnt=1;
        ll cur=x;
        while(!s.empty()&&(cur-1)/cnt+1>=s.top().first){
            auto [h,w]=s.top();
            s.pop();
            cur+=1LL*h*w;
            cnt+=w;
        }
        if(cur%cnt>0)s.emplace(cur/cnt+1,cur%cnt);
        s.emplace(cur/cnt,cnt-cur%cnt);
    }
    ll mn=LINF,mx=0;
    while(!s.empty()){
        ll x=s.top().first;
        s.pop();
        mn=min(mn,x);
        mx=max(mx,x);
    }
    cout << mx-mn << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}