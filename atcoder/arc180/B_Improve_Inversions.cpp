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
    int n,k;
    cin >> n >> k;
    vector<int> p(n),q(n);
    for(auto &x:p)cin >> x,x--;
    for(int i=0;i<n;i++)q[p[i]]=i;
    auto swapp=[&](int l,int r){
        swap(p[l],p[r]);
        swap(q[p[l]],q[p[r]]);
    };
    vector<pair<int,int>> ans;
    for(int i=0;i<n;i++){
        int x=q[i];
        for(int j=i-1;j>=0;j--)if(q[j]-x>=k){
            ans.emplace_back(x,q[j]);
            swapp(x,q[j]);
        }
    }
    cout << ans.size() << "\n";
    for(auto [l,r]:ans)cout << l+1 << " " << r+1 << "\n";
}