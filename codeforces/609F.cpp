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

struct DualSegtree{
    int n;
    vector<int> t;
    DualSegtree(int _n){init(_n);}
    void init(int _n){
        n=_n;
        int s=1;
        while(s<2*n)s*=2;
        t.assign(s,INF);
    }
    void update(int l,int r,int i,int x,int y,int v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return void(t[i]=min(t[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,int v){
        update(0,n-1,1,x,y,v);
    }
    int query(int l,int r,int i,int x){
        if(l==r)return t[i];
        int m=(l+r)/2;
        return min(t[i],x<=m?query(l,m,i*2,x):query(m+1,r,i*2+1,x));
    }
    int query(int x){
        return query(0,n-1,1,x);
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n),b(n),c(m),d(m);
    for(int i=0;i<n;i++){
        cin >> a[i] >> b[i];
    }
    for(int i=0;i<m;i++){
        cin >> c[i] >> d[i];
    }
    auto xs=a;
    xs.insert(xs.end(),c.begin(),c.end());
    sort(xs.begin(),xs.end());
    xs.erase(unique(xs.begin(),xs.end()),xs.end());
    int k=xs.size();
    DualSegtree seg(k);
    for(auto &x:a){
        x=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
    }
    for(auto &x:c){
        x=lower_bound(xs.begin(),xs.end(),x)-xs.begin();
    }
    vector<int> ans(n),id(k);
    set<pair<int,int>> s;
    auto update=[&](int i){
        auto it=s.lower_bound(make_pair(a[i],0));
        while(true){
            int j=upper_bound(xs.begin(),xs.end(),xs[a[i]]+b[i])-xs.begin()-1;
            seg.update(a[i],j,a[i]);
            if(it!=s.end()&&it->first<=j){
                ans[i]++;
                b[i]+=d[it->second];
                it=s.erase(it);
            }else{
                break;
            }
        }
    };
    for(int i=0;i<n;i++){
        id[a[i]]=i;
        update(i);
    }
    for(int i=0;i<m;i++){
        int j=seg.query(c[i]);
        if(j<k){
            j=id[j];
            ans[j]++;
            b[j]+=d[i];
            update(j);
        }else{
            s.emplace(c[i],i);
        }
    }
    for(int i=0;i<n;i++){
        cout << ans[i] << " " << b[i] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}