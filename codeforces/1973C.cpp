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
    vi a(n);
    for(auto &x:a)cin >> x;
    auto calc=[&](vi b){
        for(int i=0;i<n;i++)b[i]+=a[i];
        int res=0;
        for(int i=1;i<n-1;i++)res+=b[i]>b[i-1]&&b[i]>b[i+1];
        return res;
    };
    vector<pair<int,int>> v[2];
    for(int i=0;i<n;i++)v[i&1].emplace_back(a[i],i);
    for(int i=0;i<2;i++)sort(rall(v[i]));
    vi b(n),c(n);
    int cnt=1;
    for(auto [x,id]:v[1])if(id!=0)b[id]=cnt++;
    b[0]=cnt++;
    for(auto [x,id]:v[0])if(id!=0)b[id]=cnt++;
    cnt=1;
    for(auto [x,id]:v[0])if(id!=n-1)c[id]=cnt++;
    c[n-1]=cnt++;
    for(auto [x,id]:v[1])if(id!=n-1)c[id]=cnt++;
    if(calc(c)>calc(b))swap(c,b);
    for(auto x:b)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}