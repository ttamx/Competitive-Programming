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
    vl a(n),b(n),p(n);
    for(auto &x:b)cin >> x;
    for(auto &x:p)cin >> x,x--;
    for(int i=0;i<n;i++)a[p[i]]=b[i];
    multiset<pll> ms,ms2;
    for(int i=0;i<n;i++)ms.emplace(a[i],i);
    pll ans(0,0);
    for(int i=0;i<(n+1)/2;i++){
        while(!ms.empty()&&ms2.size()<i+1){
            ms2.emplace(*ms.rbegin());
            ms.erase(prev(ms.end()));
        }
        if(ms2.size()==i+1){
            ans=max(ans,pll(ms2.begin()->first*(i+1),-i-1));
        }
        {
            auto it=ms.find(pll(a[i],i));
            if(it!=ms.end())ms.erase(it);
        }
        {
            auto it=ms2.find(pll(a[i],i));
            if(it!=ms2.end())ms2.erase(it);
        }
    }
    cout << ans.first << " " << -ans.second << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}