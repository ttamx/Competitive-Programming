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

struct Node;
using Ptr = Node*;
struct Node{
    ll val;
    Ptr l,r;
    Node():val(0),l(),r(){}
};

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
    t->val=t->l->val+t->r->val;
}

void modify(int l,int r,Ptr &t,Ptr o,int x,int v){
    t=new Node(*o);
    if(l==r)return void(t->val=v);
    int m=(l+r)/2;
    if(x<=m)modify(l,m,t->l,o->l,x,v);
    else modify(m+1,r,t->r,o->r,x,v);
    t->val=t->l->val+t->r->val;
}

ll query(int l,int r,Ptr t,int x,int y){
    if(y<l||r<x)return 0;
    if(x<=l&&r<=y)return t->val;
    int m=(l+r)/2;
    return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
}

const int N=2e5+5;

int n,m,q;
Ptr root[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    build(1,m,root[1]);
    for(int i=2;i<=n;i++)root[i]=root[i-1];
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int x,y;
            cin >> x >> y;
            root[x]=root[y];
        }else if(op==2){
            int x,y,v;
            cin >> x >> y >> v;
            modify(1,m,root[x],root[x],y,v);
        }else{
            int x,l,r;
            cin >> x >> l >> r;
            cout << query(1,m,root[x],l,r) << "\n";
        }
    }
}