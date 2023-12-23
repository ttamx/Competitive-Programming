#include<bits/stdc++.h>
#define sz(x) (int)(x).size()
#define all(x) (x).begin(),(x).end()

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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n+2);
    for(int i=1;i<=n;i++)cin >> a[i];
    vl hsh(n+2),f(n+2),pre(n+2);
    for(int i=1;i<=n;i++)hsh[i]=rng();
    for(int i=1;i<=n;i++){
        pre[i]=pre[i-1]^hsh[i];
        f[i]=f[i-1]^hsh[a[i]];
    }
    a[0]=a[n+1]=INF;
    vi l(n+2),r(n+2);
    stack<int> s;
    s.emplace(0);
    for(int i=1;i<=n;i++){
        while(a[s.top()]<a[i])s.pop();
        l[i]=s.top()+1;
        s.emplace(i);
    }
    while(!s.empty())s.pop();
    s.emplace(n+1);
    for(int i=n;i>=1;i--){
        while(a[s.top()]<a[i])s.pop();
        r[i]=s.top()-1;
        s.emplace(i);
    }
    int ans=0;
    for(int i=1;i<=n;i++){
        l[i]=max(l[i],i-a[i]+1);
        r[i]=min(r[i],i+a[i]-1);
        if(i-l[i]<r[i]-i){
            for(int j=l[i];j<=min(i,n-a[i]+1);j++)
                if((f[j+a[i]-1]^f[j-1])==pre[a[i]])ans++;
        }else{
            for(int j=max(i,a[i]);j<=r[i];j++)
                if((f[j]^f[j-a[i]])==pre[a[i]])ans++;
        }
    }
    cout << ans;
}