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

struct Fenwick2D{
    int n,m;
    vector<vector<ll>> t;
    Fenwick2D(){}
    Fenwick2D(int _n,int _m){
        init(_n,_m);
    }
    void init(int _n,int _m){
        n=_n,m=_m;
        t.assign(n+1,vector<ll>(m+1,0LL));
    }
    void update(int x,int y,int v){
        for(int i=x+1;i<=n;i+=i&-i){
            for(int j=y+1;j<=m;j+=j&-j){
                t[i][j]+=v;
            }
        }
    }
    ll query(int x,int y){
        ll res=0;
        for(int i=x+1;i>0;i-=i&-i){
            for(int j=y+1;j>0;j-=j&-j){
                res+=t[i][j];
            }
        }
        return res;
    }
};

void runcase(){
    int n,q,k,m;
    cin >> n >> q >> k;
    vector<int> a(n);
    vector<ll> c(n);
    for(auto &x:c){
        cin >> x;
    }
    for(int i=0;i<q;i++){
        char op;
        int x;
        cin >> op >> x;
        x--;
        if(op=='L'){
            a[0]++;
            if(x+1<n){
                a[x+1]--;
            }
        }else{
            a[x]++;
        }
    }
    vector<int> aa;
    vector<ll> cc(n);
    for(int i=0;i<n;i++){
        if(a[i]>k){
            continue;
        }
        if(!aa.empty()&&a[i]==a.back()){
            cc.back()+=c[i];
        }else{
            aa.emplace_back(a[i]);
            cc.emplace_back(c[i]);
        }
    }
    swap(a,aa);
    swap(c,cc);
    int n=a.size();
    for(int v=1;v<=k;v++){
        vector<ll> dp(n);
        
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}