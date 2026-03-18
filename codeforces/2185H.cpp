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

struct Node;
using Ptr = Node*;
struct Node{
    int val;
    Ptr l,r;
    Node():val(0),l(),r(){}
};

void build(int l,int r,Ptr &t){
    t=new Node();
    if(l==r)return;
    int m=(l+r)/2;
    build(l,m,t->l);
    build(m+1,r,t->r);
}

void update(int l,int r,Ptr &t,Ptr o,int x){
    t=new Node(*o);
    t->val++;
    if(l==r)return;
    int m=(l+r)/2;
    if(x<=m)update(l,m,t->l,o->l,x);
    else update(m+1,r,t->r,o->r,x);
}

int query(int l,int r,Ptr t,int x,int y){
    if(y<l||r<x)return 0;
    if(x<=l&&r<=y)return t->val;
    int m=(l+r)/2;
    return query(l,m,t->l,x,y)+query(m+1,r,t->r,x,y);
}

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n),f(n+1),g(n);
    for(auto &x:a)cin >> x;
    for(int i=0;i<n;i++)f[i+1]=f[i]+a[i];
    for(int i=0;i<n;i++)g[i]=a[i]-f[i];
    vector<Ptr> root(n+1);
    auto vals=g;
    sort(vals.begin(),vals.end());
    build(0,n-1,root[0]);
    for(int i=0;i<n;i++){
        int idx=lower_bound(vals.begin(),vals.end(),g[i])-vals.begin();
        update(0,n-1,root[i+1],root[i],idx);
    }
    vector<int> c(n);
    for(int i=n-2;i>=0;i--){
        c[i]=c[i+1];
        if(g[i+1]>0)c[i]++;
    }
    vector<int> cnt1(n+1),cnt2(n+1);
    for(int i=0;i<n;i++)cnt1[i+1]=cnt1[i]+(c[i]<=k);
    for(int i=0;i<n;i++)cnt2[i+1]=cnt2[i]+(c[i]<k);
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        int l=i,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(f[m+1]-a[i]>=a[i])r=m;
            else l=m+1;
        }
        ans[i]+=cnt1[l]-cnt1[i];
        ans[i]+=cnt2[n]-cnt2[l];
    }
    for(int i=0;i<n;i++){
        int req=c[i];
        int l=0,r=i;
        while(l<r){
            int m=(l+r)/2;
            if(f[m]>=a[i])r=m;
            else l=m+1;
        }
        int idx=upper_bound(vals.begin(),vals.end(),a[i])-vals.begin();
        int base=query(0,n-1,root[i],idx,n-1);
        int pivot=l;
        l=0,r=pivot;
        while(l<r){
            int m=(l+r)/2;
            int cnt=base-query(0,n-1,root[m],idx,n-1);
            if(cnt+req<=k)r=m;
            else l=m+1;
        }
        ans[i]+=pivot-l;
        l=pivot,r=i;
        while(l<r){
            int m=(l+r)/2;
            int cnt=base-query(0,n-1,root[m],idx,n-1);
            if(cnt+req+1<=k)r=m;
            else l=m+1;
        }
        ans[i]+=i-l;
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}