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
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    auto check=[&](int x){
        int cnt=0;
        function<int(int,int)> dfs=[&](int u,int p){
            int s=1;
            for(auto v:adj[u])if(v!=p){
                s+=dfs(v,u);
            }
            if(s>=x){
                cnt++;
                s=0;
            }
            return s;
        };
        dfs(0,-1);
        return cnt>=k+1;
    };
    int l=1,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(m))l=m;
        else r=m-1;
    }
    cout << l << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}