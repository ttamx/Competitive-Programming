#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

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

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int ans=0;
    vector<vector<bool>> vis(n,vector<bool>(m));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='#'){
                vis[i][j]=true;
            }
        }
    }
    auto valid=[&](int i,int j){
        return 0<=i&&i<n&&0<=j&&j<m&&!vis[i][j];
    };
    function<void(int,int,int)> rec=[&](int i,int j,int d){
        if(d==k){
            ans++;
            return;
        }
        vis[i][j]=true;
        if(valid(i-1,j))rec(i-1,j,d+1);
        if(valid(i,j-1))rec(i,j-1,d+1);
        if(valid(i,j+1))rec(i,j+1,d+1);
        if(valid(i+1,j))rec(i+1,j,d+1);
        vis[i][j]=false;
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(!vis[i][j]){
                rec(i,j,0);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}