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
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        p--;
        adj[p].emplace_back(i);
    }
    function<void(int)> dfs=[&](int u){
        ll mn=LINF;
        for(auto v:adj[u]){
            dfs(v);
            mn=min(mn,a[v]);
        }
        if(mn==LINF)return;
        if(u==0){
            a[u]+=mn;
        }else if(a[u]<mn){
            a[u]+=(mn-a[u])/2;
        }else{
            a[u]=mn;
        }
    };
    dfs(0);
    cout << a[0] << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}