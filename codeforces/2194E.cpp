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
    vector<vector<ll>> a(n,vector<ll>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    vector<vector<ll>> pre(n,vector<ll>(m,-LINF));
    vector<vector<ll>> suf(n,vector<ll>(m,-LINF));
    pre[0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(i+1<n)pre[i+1][j]=max(pre[i+1][j],pre[i][j]+a[i][j]);
            if(j+1<m)pre[i][j+1]=max(pre[i][j+1],pre[i][j]+a[i][j]);
        }
    }
    suf[n-1][m-1]=0;
    for(int i=n-1;i>=0;i--){
        for(int j=m-1;j>=0;j--){
            if(i>0)suf[i-1][j]=max(suf[i-1][j],suf[i][j]+a[i][j]);
            if(j>0)suf[i][j-1]=max(suf[i][j-1],suf[i][j]+a[i][j]);
        }
    }
    ll ans=LINF;
    vector<vector<pair<int,int>>> pos(n+m-1);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            pos[i+j].emplace_back(i,j);
        }
    }
    for(auto &v:pos){
        int k=v.size();
        vector<ll> pre2(k,-LINF),suf2(k,-LINF);
        for(int i=0;i+1<k;i++){
            auto [x,y]=v[i];
            pre2[i+1]=max(pre2[i],a[x][y]+pre[x][y]+suf[x][y]);
        }
        for(int i=k-1;i>0;i--){
            auto [x,y]=v[i];
            suf2[i-1]=max(suf2[i],a[x][y]+pre[x][y]+suf[x][y]);
        }
        for(int i=0;i<k;i++){
            auto [x,y]=v[i];
            ans=min(ans,max({pre2[i],suf2[i],-a[x][y]+pre[x][y]+suf[x][y]}));
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