#include<bits/stdc++.h>

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

const int N=1e6+5;

bool notprime[N];
vector<int> factors[N];

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> p;
    map<int,vector<int>> mp;
    for(int i=0;i<n;i++){
        for(auto x:factors[a[i]])mp[x].emplace_back(i);
    }
    vector<int> fa(2*n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int x){
        return fa[x]==x?x:fa[x]=fp(fa[x]);
    };
    auto uni=[&](int x,int y){
        x=fp(x),y=fp(y);
        if(x!=y)fa[x]=y;
    };
    for(auto [x,v]:mp){
        int m=v.size();
        for(int i=0;i<m;i++)v.emplace_back(v[i]+n);
        for(int i=v[0]==0?2:1;i<v.size();i++)if(v[i]-v[i-1]<=k)uni(v[i-1],v[i]);
    }
    ll ans=0;
    for(auto x:a)if(x==1)ans+=n;
    for(int i=1;i<2*n;i++)if(a[i%n]!=1&&fp(i)==i)ans++;
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<N;i++)if(!notprime[i]){
        for(int j=i;j<N;j+=i){
            factors[j].emplace_back(i),notprime[j]=true;
        }
    }
    int t(1);
    cin >> t;
    while(t--)runcase();
}