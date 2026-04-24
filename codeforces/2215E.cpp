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
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a)cin >> x >> y;
    vector<int> ord(n);
    iota(ALL(ord),0);
    sort(ALL(ord),[&](int i,int j){return a[i]<a[j];});
    vector<int> top{ord[0]},bot{ord[0]};
    vector<tuple<int,int,int>> ans;
    for(int i=1;i<n;i++){
        int u=ord[i],v=ord[i-1];
        if(a[u].se>a[v].se){
            while(SZ(top)>=2&&a[top.back()].se<a[u].se){
                ans.eb(u,top.back(),top.end()[-2]);
                top.pop_back();
            }
            if(a[top.back()].se<a[u].se)top.pop_back();
        }else{
            while(SZ(bot)>=2&&a[bot.back()].se>a[u].se){
                ans.eb(u,bot.back(),bot.end()[-2]);
                bot.pop_back();
            }
            if(a[bot.back()].se>a[u].se)bot.pop_back();
        }
        top.eb(u);
        bot.eb(u);
    }
    cout << SZ(ans) << "\n";
    for(auto [x,y,z]:ans){
        cout << x+1 << " " << y+1 << " " << z+1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}