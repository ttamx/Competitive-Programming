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

vi z_algorithm(const string &s){
    int n=sz(s);
    vi z(n);
    for(int i=1,l=0,r=0;i<n;i++){
        if(i<=r)z[i]=min(r-i+1,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]-1>r)l=i,r=i+z[i]-1;
    }
    return z;
}

void runcase(){
    string s;
    cin >> s;
    int n=sz(s);
    int p=0;
    while(p<n&&s[p]=='a')p++;
    if(p==n)return void(cout << n-1 << "\n");
    vi nxt(n);
    for(int i=n-1,j=n;i>=0;i--){
        if(s[i]=='a')nxt[i]=j;
        else nxt[i]=j=i;
    }
    ll ans=0;
    auto z=z_algorithm(s.substr(p,n));
    auto calc=[&](int k){
        int gap=p;
        for(int i=p+k;i<n&&nxt[i]<n;i+=k){
            gap=min(gap,nxt[i]-i);
            i=nxt[i];
            if(z[i-p]<k)return;
        }
        ans+=gap+1;
    };
    for(int i=1;i<=n-p;i++)calc(i);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}