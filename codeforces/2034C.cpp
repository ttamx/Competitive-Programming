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
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<vector<bool>> vis(n,vector<bool>(m)),bad(n,vector<bool>(m));
    function<bool(int,int)> dfs=[&](int i,int j)->bool{
        if(i<0||i>=n||j<0||j>=m)return true;
        if(vis[i][j])return bad[i][j];
        vis[i][j]=true;
        if(a[i][j]=='U')return bad[i][j]=dfs(i-1,j);
        if(a[i][j]=='D')return bad[i][j]=dfs(i+1,j);
        if(a[i][j]=='L')return bad[i][j]=dfs(i,j-1);
        if(a[i][j]=='R')return bad[i][j]=dfs(i,j+1);
        return bad[i][j]=false;
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]!='?'&&!vis[i][j]){
                dfs(i,j);
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]!='?'){
                if(!bad[i][j]){
                    ans++;
                }
            }
        }
    }
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='?'){
                if(i>0&&!bad[i-1][j]){
                    ans++;
                }else if(i<n-1&&!bad[i+1][j]){
                    ans++;
                }else if(j>0&&!bad[i][j-1]){
                    ans++;
                }else if(j<m-1&&!bad[i][j+1]){
                    ans++;
                }
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}