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
    vl a(n),b(n),c(n);
    for(auto &x:a)cin >> x;
    b[0]=0,b[1]=1;
    for(int i=1;i<n-1;i++){
        ll l=a[i]-a[i-1],r=a[i+1]-a[i];
        if(r<l){
            b[i+1]=b[i]+1;
        }else{
            b[i+1]=b[i]+r;
        }
    }
    c[n-1]=0,c[n-2]=1;
    for(int i=n-2;i>0;i--){
        ll l=a[i]-a[i-1],r=a[i+1]-a[i];
        if(l<r){
            c[i-1]=c[i]+1;
        }else{
            c[i-1]=c[i]+l;
        }
    }
    int q;
    cin >> q;
    while(q--){
        int u,v;
        cin >> u >> v;
        u--,v--;
        if(u<v){
            cout << b[v]-b[u] << "\n";
        }else{
            cout << c[v]-c[u] << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}