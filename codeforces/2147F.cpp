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

const int N=1e5+5;
const int B=320;

int n,q,b;
int p[N],s[N],a[N];
int mxx[B];
int L[N],R[N],id[N];

struct Info{
    ll st,ed,val,base;
    friend Info operator+(const Info &l,const Info &r){
        if(l.st==0)return r;
        if(r.st==0)return l;
        Info res=l;
        res.ed=r.ed;
        res.base+=(r.st-l.ed)*r.val+r.base;
        return res;
    }
}val[B][B];

void build(int blk){
    int l=L[blk],r=R[blk];
    int mx=0;
    for(int i=l,j=0;i<=r;i++,j++){
        mx=max(mx,a[i]);
        if(mx<=i){
            val[blk][j]=Info{i,i,i,0};
        }else{
            val[blk][j]=Info{0,0,0,0};
        }
    }
    for(int i=r-l-1;i>=0;i--){
        val[blk][i]=val[blk][i]+val[blk][i+1];
    }
    mxx[blk]=mx;
}

void runcase(){
    cin >> n >> q;
    b=1;
    while(b*b<n)b++;
    for(int i=1;i<=n;i++){
        cin >> p[i];
    }
    for(int i=1;i<=n;i++){
        cin >> s[i];
    }
    for(int i=1;i<=n;i++){
        a[p[i]]=s[i];
    }
    int buf=0;
    for(int l=1,r=b;l<=n;l+=b,r+=b,buf++){
        r=min(r,n);
        L[buf]=l;
        R[buf]=r;
        for(int j=l;j<=r;j++){
            id[j]=buf;
        }
    }
    for(int i=0;i<buf;i++){
        build(i);
    }
    while(q--){
        int op,x,y;
        cin >> op >> x >> y;
        if(op==1){
            swap(p[x],p[y]);
        }else{
            swap(s[x],s[y]);
        }
        swap(a[p[x]],a[p[y]]);
        build(id[p[x]]);
        build(id[p[y]]);
        Info res{0,0,0,0};
        int mx=0;
        for(int i=0;i<buf;i++){
            int l=L[i],r=R[i];
            mx=max(mx,l);
            if(mx<=r)res=res+val[i][mx-l];
            mx=max(mx,mxx[i]);
        }
        cout << res.base+res.st*res.val << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}