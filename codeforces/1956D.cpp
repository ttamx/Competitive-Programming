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

int n;
int a[18];
pll ans;
vector<pii> ops;

void build(int l,int r){
    if(l>r)return;
    if(l==r){
        if(a[l]!=1){
            if(a[l])ops.emplace_back(l,l);
            ops.emplace_back(l,l);
            a[l]=1;
        }
        return;
    }
    for(int i=l;i<r;i++){
        build(i,r-1);
    }
    if(a[r])ops.emplace_back(r,r);
    ops.emplace_back(l,r);
    for(int i=l;i<=r;i++)a[i]=r-l+1;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++)cin >> a[i];
    for(int mask=0;mask<1<<n;mask++){
        int p=0;
        ll res=0;
        for(int i=0;i<n;i++)if(mask>>i&1){
            res+=a[i]+(i-p)*(i-p);
            p=i+1;
        }
        res+=(n-p)*(n-p);
        ans=max(ans,pll(res,mask));
    }
    int p=0;
    for(int i=0;i<n;i++)if(ans.second>>i&1){
        build(p,i-1);
        p=i+1;
    }
    build(p,n-1);
    cout << ans.first << " " << sz(ops) << "\n";
    for(auto [l,r]:ops)cout << l+1 << " " << r+1 << "\n";
}