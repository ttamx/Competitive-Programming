#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

#define pb push_back
#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define ALL(a) (a).begin(),(a).end()
#define RALL(a) (a).rbegin(),(a).rend()
#define SORT(a) sort(ALL(a))
#define RSORT(a) sort(RALL(a))
#define REV(a) reverse(ALL(a))
#define UNI(a) (a).erase(unique(ALL(a)),(a).end())
#define SZ(a) (int)(a).size()
#define LB(a,x) (int)(lower_bound(ALL(a),x)-(a).begin())
#define UB(a,x) (int)(upper_bound(ALL(a),x)-(a).begin())

using ll = long long;
using db = long double;
using vi = vector<int>;
using vvi = vector<vector<int>>;
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

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

const int K=1<<21;

struct Segtree{
    int t[K],lz[K];
    void apply(int i,int v){
        t[i]=max(t[i],v);
        lz[i]=max(lz[i],v);
    }
    void push(int i){
        apply(i*2,lz[i]);
        apply(i*2+1,lz[i]);
        lz[i]=0;
    }
    void pull(int i){
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i,v);
        push(i);
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        pull(i);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return INF;
        if(x<=l&&r<=y)return t[i];
        push(i);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}seg;

void runcase(){
    int n,vx,vy;
    cin >> n >> vx >> vy;
    vvi a(n,vi(n));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    if(vx<0){
        vx*=-1;
        REV(a);
    }
    if(vy<0){
        vy*=-1;
        for(auto &v:a){
            REV(v);
        }
    }
    auto calc=[&](int x,int y){
        return x*vy-y*vx;
    };
    vi vec;
    for(int i=0;i<=n;i++){
        for(int j=0;j<=n;j++){
            vec.eb(calc(i,j));
        }
    }
    SORT(vec);
    UNI(vec);
    int m=SZ(vec);
    ll ans=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            int l=LB(vec,calc(i,j+1)),r=LB(vec,calc(i+1,j))-1;
            ans+=max(0,a[i][j]-seg.query(0,m-1,1,l,r));
            seg.update(0,m-1,1,l,r,a[i][j]);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}