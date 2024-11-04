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
    ll w;
    cin >> n >> m >> w;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    auto bfs=[&](int si,int sj){
        vector<vector<int>> dist(n,vector<int>(m,-1));
        queue<pair<int,int>> q;
        dist[si][sj]=0;
        q.emplace(si,sj);
        auto go=[&](int i,int j,int d){
            if(0<=i&&i<n&&0<=j&&j<m&&a[i][j]!=-1&&dist[i][j]==-1){
                dist[i][j]=d+1;
                q.emplace(i,j);
            }
        };
        while(!q.empty()){
            auto [i,j]=q.front();
            q.pop();
            go(i-1,j,dist[i][j]);
            go(i,j-1,dist[i][j]);
            go(i,j+1,dist[i][j]);
            go(i+1,j,dist[i][j]);
        }
        return dist;
    };
    auto dist1=bfs(0,0);
    auto dist2=bfs(n-1,m-1);
    ll ans=LINF;
    if(dist1[n-1][m-1]!=-1){
        ans=dist1[n-1][m-1]*w;
    }
    ll val1=LINF,val2=LINF;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j]>0){
                if(dist1[i][j]!=-1){
                    val1=min(val1,dist1[i][j]*w+a[i][j]);
                }
                if(dist2[i][j]!=-1){
                    val2=min(val2,dist2[i][j]*w+a[i][j]);
                }
            }
        }
    }
    ans=min(ans,val1+val2);
    cout << (ans<LINF?ans:-1LL) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}