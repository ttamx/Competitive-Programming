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
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    sort(b.begin(),b.end());
    int s=n%k;
    if(s==0)s=k;
    auto check=[&](int x){
        vector<int> dp(s,-INF);
        for(int i=0;i<n;i++){
            int j=i%k;
            if(j>=s)continue;
            dp[j]=max(dp[j],(j?dp[j-1]:0)+(a[i]>=x));
        }
        return dp[s-1]>s/2;
    };
    int l=0,r=n-1;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(b[m]))l=m;
        else r=m-1;
    }
    cout << b[l] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}