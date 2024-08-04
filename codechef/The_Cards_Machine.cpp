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

struct Info{
    int i,val,gap;
    bool ok;
    Info(int _i,int _val,int _gap):i(_i),val(_val),gap(_gap),ok(false){}
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<Info> s;
    int cur=0;
    vector<ll> dp(n);
    for(int i=0;i<n;i++){
        while(!s.empty()&&s.back().val<a[i]){
            auto x=s.back();
            s.pop_back();
            if(x.ok)cur-=x.gap;
        }
        if(!s.empty()){
            auto &x=s.back();
            if(a[i]==x.val){
                x.ok=true;
                cur+=x.gap;
            }
            s.emplace_back(i,a[i],i-x.i);
        }else{
            s.emplace_back(i,a[i],i+1);
        }
        dp[i]=cur;
    }
    for(int i=1;i<n;i++)dp[i]+=dp[i-1];
    int q;
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        cout << dp[n-x-1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}