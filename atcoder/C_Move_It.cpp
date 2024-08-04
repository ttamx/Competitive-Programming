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
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> w(n);
    vector<vector<int>> a(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x-1].emplace_back(i);
    }
    int ans=0;
    for(auto &x:w)cin >> x,ans+=x;
    for(auto v:a){
        int mx=0;
        for(auto x:v)mx=max(mx,w[x]);
        ans-=mx;
    }
    cout << ans;
}