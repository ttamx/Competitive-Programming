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
const int Q=1e4+5;
const int S=320;

int n,q,m;
int a[N],b[N],x[Q],y[Q];
vector<ll> vals;
vector<int> qrs[S];
ll ans[Q];
ll base=0LL;

struct Fenwick{
    ll t[2*N];
    void update(int i,ll v){
        for(;i<=m;i+=i&-i)t[i]+=v;
    }
    ll query(int i){
        ll res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    ll query(int l,int r){
        return query(r)-query(l-1);
    }
}fas,fac,fbs,fbc;

void update_a(int i,int mul){
    ll x=vals[a[i]-1];
    fas.update(a[i],x*mul);
    fac.update(a[i],mul);
    ll ps=fbs.query(a[i]);
    ll pc=fbc.query(a[i]);
    ll ss=fbs.query(m)-ps;
    ll sc=fbc.query(m)-pc;
    base+=(x*pc-ps+ss-x*sc)*mul;
}

void update_b(int i,int mul){
    ll x=vals[b[i]-1];
    fbs.update(b[i],x*mul);
    fbc.update(b[i],mul);
    ll ps=fas.query(b[i]);
    ll pc=fac.query(b[i]);
    ll ss=fas.query(m)-ps;
    ll sc=fac.query(m)-pc;
    base+=(x*pc-ps+ss-x*sc)*mul;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        vals.emplace_back(a[i]);
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
        vals.emplace_back(b[i]);
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    m=vals.size();
    for(int i=1;i<=n;i++){
        a[i]=lower_bound(vals.begin(),vals.end(),a[i])-vals.begin()+1;
        b[i]=lower_bound(vals.begin(),vals.end(),b[i])-vals.begin()+1;
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        cin >> x[i] >> y[i];
        qrs[(x[i]-1)/S].emplace_back(i);
    }
    qrs[1].emplace_back(0);
    int pa=0,pb=0;
    for(int s=0;s<S;s++){
        auto &qr=qrs[s];
        sort(qr.begin(),qr.end(),[&](int i,int j){return y[i]<y[j];});
        for(auto i:qr){
            while(pa<x[i])update_a(++pa,+1);
            while(pa>x[i])update_a(pa--,-1);
            while(pb<y[i])update_b(++pb,+1);
            while(pb>y[i])update_b(pb--,-1);
            ans[i]=base;
        }
    }
    for(int i=1;i<=q;i++){
        cout << ans[i] << "\n";
    }
}