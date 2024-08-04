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
    ll ans=0;
    for(int t=0;t<2;t++){
        vector<int> b(n),cnt(n+1);
        int mx=0;
        for(int i=0;i<n;i++){
            ans+=a[i];
            cnt[a[i]]++;
            if(cnt[a[i]]>=2)mx=max(mx,a[i]);
            b[i]=mx;
        }
        swap(a,b);
    }
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&a[j+1]==a[i])j++;
        int s=j-i+1;
        ans+=1LL*a[i]*s*(s+1)/2;
        ans+=1LL*(n-j-1)*s*a[i];
        i=j;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}