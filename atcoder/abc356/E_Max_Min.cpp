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

const int X=1e6+5;

int cnt[X],cum[X];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x]++;
    }
    for(int i=1;i<X;i++)cum[i]=cum[i-1]+cnt[i];
    ll ans=0;
    for(int i=1;i<X;i++){
        ll pre=ans;
        ans+=1LL*cnt[i]*(cnt[i]-1)/2;
        ans+=1LL*(cum[min(X-1,2*i-1)]-cum[i])*cnt[i];
        for(int j=2;j*i<X;j++)ans+=1LL*(cum[min(X-1,(j+1)*i-1)]-cum[j*i-1])*cnt[i]*j;
    }
    cout << ans;
}