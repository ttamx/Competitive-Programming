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

int n=999,m=500;
int x,y;
int a[N][N];
int px[N],py[N];
int row[N],col[N];
int cnt[2][2];

void update(int x,int y,int v){
    a[x][y]+=v;
    row[x]+=v;
    col[y]+=v;
}

void query(int xx,int yy){
    if(a[xx][yy]){
        for(int dx=-1;dx<=1;dx++){
            for(int dy=-1;dy<=1;dy++){
                int nx=x+dx,ny=y+dy;
                if(!a[nx][ny]&&(row[nx]||col[ny])){
                    xx=nx;
                    yy=ny;
                }
            }
        }
    }
    cout << xx << " " << yy << endl;
    x=xx,y=yy;
    int k,nx,ny;
    cin >> k >> nx >> ny;
    if(k==-1)exit(0);
    update(px[k],py[k],-1);
    px[k]=nx,py[k]=ny;
    update(px[k],py[k],+1);
}

void go(int xx,int yy){
    while(x!=xx||y!=yy){
        int nx=x,ny=y;
        if(x<xx)nx++;
        if(x>xx)nx--;
        if(y<yy)ny++;
        if(y>yy)ny--;
        query(nx,ny);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> x >> y;
    for(int i=1;i<=666;i++){
        cin >> px[i] >> py[i];
        update(px[i],py[i],+1);
    }
    go(m,m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            cnt[i>m][j>m]+=a[i][j];
        }
    }
    int mn=INF,xx=0,yy=0;
    for(int i=0;i<2;i++){
        for(int j=0;j<2;j++){
            if(cnt[i][j]<mn){
                mn=cnt[i][j];
                xx=i?1:n;
                yy=j?1:n;
            }
        }
    }
    go(xx,yy);
}