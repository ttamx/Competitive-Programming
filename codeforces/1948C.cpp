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
    string s[2];
    cin >> s[0] >> s[1];
    auto calc=[&](int i,int j){
        return j+(s[i][j]=='<'?-1:1);
    };
    vector<vector<bool>> vis(2,vector<bool>(n));
    function<void(int,int)> dfs=[&](int i,int j){
        if(vis[i][j])return;
        vis[i][j]=true;
        dfs(i^1,calc(i^1,j));
        if(j>0)dfs(i,calc(i,j-1));
        if(j+1<n)dfs(i,calc(i,j+1));
    };
    dfs(0,0);
    cout << ((vis[0][n-1]||vis[1][n-1])?"YES":"NO") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}