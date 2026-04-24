#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define ALL(a) a.begin(),a.end()
#define RALL(a) a.rbegin(),a.rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) a.erase(unique(ALL(a)),a.end())
#define SZ(a) (int)(a.size())
#define LB(a,x) (int)(lower_bound(ALL(a),x)-a.begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-a.begin())
#define MIN(a) *min_element(ALL(a))
#define MAX(a) *max_element(ALL(a))

using ll = long long;
using db = long double;
using i128 = __int128_t;
using u32 = uint32_t;
using u64 = uint64_t;

const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/4;
const db DINF=numeric_limits<db>::infinity();
const int MOD=998244353;
const int MOD2=1000000007;
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;
template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;

#define vv(T,a,n,...) vector<vector<T>> a(n,vector<T>(__VA_ARGS__))
#define vvv(T,a,n,m,...) vector<vector<vector<T>>> a(n,vector<vector<T>>(m,vector<T>(__VA_ARGS__)))
#define vvvv(T,a,n,m,k,...) vector<vector<vector<vector<T>>>> a(n,vector<vector<vector<T>>>(m,vector<vector<T>>(k,vector<T>(__VA_ARGS__))))

template<class T,class U>
bool chmin(T &a,U b){return b<a?a=b,1:0;}
template<class T,class U>
bool chmax(T &a,U b){return a<b?a=b,1:0;}
template<class T,class U>
T SUM(const U &a){return accumulate(ALL(a),T{});}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

void runcase(){
    int n,m;
    cin >> n >> m;
    vv(int,a,n,m);
    vv(int,b,n,m);
    for(auto &v:a)for(auto &x:v)cin >> x;
    for(auto &v:b)for(auto &x:v)cin >> x;
    vector<int> cnt(m);
    vector<vector<int>> adj(n);
    vector<int> q;
    for(int i=0;i<m;i++){
        for(int j=0;j+1<n;j++){
            if(b[j][i]>b[j+1][i]){
                cnt[i]++;
                adj[j].emplace_back(i);
            }
        }
        if(cnt[i]==0)q.eb(i);
    }
    for(int i=0;i<SZ(q);i++){
        int p=q[i];
        for(int j=0;j+1<n;j++){
            if(b[j][p]<b[j+1][p]){
                for(auto x:adj[j]){
                    if(--cnt[x]==0)q.eb(x);
                }
                adj[j].clear();
            }
        }
    }
    REV(q);
    vector<int> ord(n);
    iota(ALL(ord),0);
    for(auto i:q){
        stable_sort(ALL(ord),[&](int x,int y){return a[x][i]<a[y][i];});
    }
    for(int i=0;i<n;i++)if(a[ord[i]]!=b[i]){
        cout << -1 << "\n";
        return;
    }
    cout << SZ(q) << "\n";
    for(auto i:q){
        cout << i+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}