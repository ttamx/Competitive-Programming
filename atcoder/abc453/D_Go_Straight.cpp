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

const int N=1005;

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};
string dir="ULDR";

int n,m;
string a[N];
bool vis[N][N][4];
tuple<int,int,int> par[N][N][4];
int si,sj;
queue<tuple<int,int,int>> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
        for(int j=0;j<m;j++){
            if(a[i][j]=='S'){
                si=i,sj=j;
            }
        }
    }
    for(int d=0;d<4;d++){
        int ii=si+dx[d];
        int jj=sj+dy[d];
        if(ii<0||ii>=n||jj<0||jj>=m||a[ii][jj]=='#'||vis[ii][jj][d])continue;
        vis[ii][jj][d]=true;
        par[ii][jj][d]={si,sj,-1};
        q.emplace(ii,jj,d);
    }
    while(!q.empty()){
        auto [i,j,k]=q.front();
        q.pop();
        if(a[i][j]=='G'){
            string ans="";
            while(k!=-1){
                ans.pb(dir[k]);
                tie(i,j,k)=par[i][j][k];
            }
            REV(ans);
            cout << "Yes\n";
            cout << ans << "\n";
            exit(0);
        }
        for(int d=0;d<4;d++){
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(ii<0||ii>=n||jj<0||jj>=m||a[ii][jj]=='#'||vis[ii][jj][d])continue;
            if(a[i][j]=='o'&&d!=k)continue;
            if(a[i][j]=='x'&&d==k)continue;
            vis[ii][jj][d]=true;
            par[ii][jj][d]={i,j,k};
            q.emplace(ii,jj,d);
        }
    }
    cout << "No\n";
}