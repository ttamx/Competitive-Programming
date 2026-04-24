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

const int N=4e5+5;
const int X=2e5+5;
const int Q=1e5+5;

int n,q;
int a[N],opt[N],opt2[N];
int lp[X];
vector<int> pos[X],adj[N];
vector<pair<int,int>> qr[N];
tuple<int,int,int> ans[Q];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=2;i<X;i++){
        if(lp[i])continue;
        for(int j=i;j<X;j+=i){
            if(!lp[j])lp[j]=i;
        }
    }
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        for(int v=a[i];v>1;){
            int p=lp[v];
            while(v%p==0)v/=p;
            pos[p].eb(i);
        }
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int l,r;
        cin >> l >> r;
        qr[r].emplace_back(l,i);
    }
    for(int i=2;i<X;i++){
        if(lp[i]!=i)continue;
        int m=pos[i].size();
        for(int j=0;j+1<m;j++){
            adj[pos[i][j+1]].eb(pos[i][j]);
        }
        for(int j=0;j+2<m;j++){
            int u=pos[i][j],v=pos[i][j+1],w=pos[i][j+2];
            if(opt[w]<u){
                opt[w]=u;
                opt2[w]=v;
            }
        }
    }
    int x=0,y=0,z=0;
    for(int i=1;i<=n;i++){
        if(opt[i]>x){
            x=opt[i],y=opt2[i],z=i;
        }
        for(auto j:adj[i]){
            for(auto k:adj[i]){
                if(j<k&&j>x&&gcd(a[j],a[k])>1){
                    x=j,y=k,z=i;
                }
            }
        }
        for(auto [l,j]:qr[i]){
            if(l>x)ans[j]={-1,-1,-1};
            else ans[j]={x,y,z};
        }
    }
    for(int i=1;i<=q;i++){
        auto [x,y,z]=ans[i];
        if(x==-1){
            cout << -1 << "\n";
        }else{
            cout << x << " " << y << " " << z << "\n";
        }
    }
}