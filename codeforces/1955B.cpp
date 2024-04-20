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
    ll c,d;
    cin >> n >> c >> d;
    multiset<ll> ms;
    for(int i=0;i<n*n;i++){
        ll x;
        cin >> x;
        ms.emplace(x);
    }
    vector<vl> a(n,vl(n));
    a[0][0]=*ms.begin();
    ms.erase(ms.begin());
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        if(i+1<n&&!a[i+1][j]){
            ll x=a[i][j]+c;
            a[i+1][j]=x;
            auto it=ms.find(x);
            if(it==ms.end())return void(cout << "NO\n");
            ms.erase(it);
        }
        if(j+1<n&&!a[i][j+1]){
            ll x=a[i][j]+d;
            a[i][j+1]=x;
            auto it=ms.find(x);
            if(it==ms.end())return void(cout << "NO\n");
            ms.erase(it);
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}