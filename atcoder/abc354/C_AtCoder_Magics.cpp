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

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vi a(n),c(n);
    for(int i=0;i<n;i++)cin >> a[i] >> c[i];
    vi ord(n);
    iota(all(ord),0);
    sort(all(ord),[&](int i,int j){
        return c[i]<c[j];
    });
    vi del(n);
    int mx=0;
    for(auto i:ord){
        if(mx>a[i])del[i]=1;
        else mx=a[i];
    }
    vi ans;
    for(int i=0;i<n;i++)if(!del[i])ans.emplace_back(i+1);
    cout << sz(ans) << "\n";
    for(auto x:ans)cout << x << " ";
}