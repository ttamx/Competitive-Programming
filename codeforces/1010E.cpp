#pragma GCC optimize("Ofast,unroll-loops")
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

const int N=1e5+5;

struct Segtree{
    struct Node;
    using Ptr = Node*;
    struct Node{
        int val;
        Ptr l,r;
        Node():val(0),l(),r(){}
    };
    Ptr root;
    Segtree():root(){}
    void update(int l,int r,Ptr &t,int x,int v){
        if(!t)t=new Node();
        t->val+=v;
        if(l==r)return;
        int m=(l+r)/2;
        if(x<=m)update(l,m,t->l,x,v);
        else update(m+1,r,t->r,x,v);
    }
    void update(int x,int v){
        update(1,N,root,x,v);
    }
    int query(int l,int r,Ptr t,int x,int y){
        if(y<l||r<x||!t)return 0;
        if(x<=l&&r<=y)return t->val;
        int m=(l+r)/2;
        return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
    }
    int query(int x,int y){
        return query(1,N,root,x,y);
    }
};

struct BITSeg{
    Segtree t[N];
    void update(int i,int x,int v){
        for(;i<N;i+=i&-i)t[i].update(x,v);
    }
    int query(int i,int x,int y){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i].query(x,y);
        return res;
    }
    int query(int l,int r,int x,int y){
        return query(r,x,y)-query(l-1,x,y);
    }
}ds;

int _,n,m,k;
int xmn,xmx,ymn,ymx,zmn,zmx;
vector<pair<int,int>> pts[N];
vector<tuple<int,int,int,int,int,int>> qr[N];
int ans[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> _ >> _ >> _ >> n >> m >> k;
    xmn=ymn=zmn=INF;
    xmx=ymx=zmx=-INF;
    for(int i=0;i<n;i++){
        int x,y,z;
        cin >> x >> y >> z;
        chmin(xmn,x);
        chmax(xmx,x);
        chmin(ymn,y);
        chmax(ymx,y);
        chmin(zmn,z);
        chmax(zmx,z);
    }
    for(int i=0;i<m;i++){
        int x,y,z;
        cin >> x >> y >> z;
        pts[x].emplace_back(y,z);
        if(xmn<=x&&x<=xmx&&ymn<=y&&y<=ymx&&zmn<=z&&z<=zmx){
            cout << "INCORRECT\n";
            exit(0);
        }
    }
    for(int i=0;i<k;i++){
        int x,y,z;
        cin >> x >> y >> z;
        if(xmn<=x&&x<=xmx&&ymn<=y&&y<=ymx&&zmn<=z&&z<=zmx){
            ans[i]=-1;
        }else{
            int xl=min(xmn,x);
            int xr=max(xmx,x);
            int yl=min(ymn,y);
            int yr=max(ymx,y);
            int zl=min(zmn,z);
            int zr=max(zmx,z);
            qr[xl-1].emplace_back(yl,yr,zl,zr,i,-1);
            qr[xr].emplace_back(yl,yr,zl,zr,i,+1);
        }
    }
    for(int i=0;i<N;i++){
        for(auto [x,y]:pts[i]){
            ds.update(x,y,1);
        }
        for(auto [xl,xr,yl,yr,j,mul]:qr[i]){
            ans[j]+=mul*ds.query(xl,xr,yl,yr);
        }
    }
    cout << "CORRECT\n";
    for(int i=0;i<k;i++){
        if(ans[i]==-1){
            cout << "OPEN\n";
        }else if(ans[i]==0){
            cout << "UNKNOWN\n";
        }else{
            cout << "CLOSED\n";
        }
    }
}