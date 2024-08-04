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
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    ll ans=0;
    vector<int> d(n-1);
    for(int i=0;i<n-1;i++)d[i]=a[i+1]-a[i];
    auto calc=[&](ll x){
        return x*x*(x+1)/2-x*(x+1)*(2*x+1)/6;
    };
    for(int i=0;i<n-1;i++)if(d[i]==1){
        int j=i+1;
        while(j<n-1&&d[j]==1)j++;
        ans+=calc(j-i);
        i=j-1;
    }
    for(int i=0;i<n-1;i++)if(d[i]==2){
        int l=i,r=i;
        while(l>0&&d[l-1]==1)l--;
        while(r<n-2&&d[r+1]==1)r++;
        ans+=1LL*(i-l+1)*(r-i+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}