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
    int n,m,d;
    cin >> n >> m >> d;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
    }
    queue<pair<int,int>> q;
    vector<vector<int>> ds(n,vector<int>(m,INF));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]=='H'){
                q.emplace(i,j);
                ds[i][j]=0;
            }
        }
    }
    auto go=[&](int i,int j,int d){
        if(i<0||i>=n||j<0||j>=m||a[i][j]=='#'||ds[i][j]<=d)return;
        q.emplace(i,j);
        ds[i][j]=d;
    };
    int ans=0;
    while(!q.empty()){
        auto [i,j]=q.front();
        q.pop();
        if(ds[i][j]<=d){
            ans++;
        }
        int d=ds[i][j]+1;
        go(i-1,j,d);
        go(i,j-1,d);
        go(i,j+1,d);
        go(i+1,j,d);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}