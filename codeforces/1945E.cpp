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
    int n,k;
    cin >> n >> k;
    vi a(n);
    for(auto &x:a)cin >> x;
    vi b;
    vector<pii> ans;
    int l=0,r=n;
    int pos=0,pos2=-1;
    for(int i=0;i<n;i++)if(a[i]==k)pos=i;
    while(r-l>1){
        int m=(l+r)/2;
        if(a[m]==k)pos2=m;
        if(a[m]<=k){
            for(int i=l;i<m;i++)b.emplace_back(i);
            l=m;
        }else{
            for(int i=m+1;i<r;i++)b.emplace_back(i);
            r=m;
        }
    }
    if(a[l]!=k)ans.emplace_back(l,pos);
    if(pos2!=-1&&pos2!=l)for(auto i:b)if(a[i]<k){
        ans.emplace_back(i,pos2);
        break;
    }
    cout << sz(ans) << "\n";
    for(auto [x,y]:ans)cout << x+1 << " " << y+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}