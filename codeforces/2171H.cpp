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

struct Fenwick{
    int n;
    vector<int> t;
    Fenwick(int n=0){init(n);}
    void init(int _n){
        n=_n;
        t.assign(n+1,-INF);
    }
    void update(int i,const int &v){
        for(;i<=n;i+=i&-i)t[i]=max(t[i],v);
    }
    int query(int i){
        int res=-INF;
        for(;i>0;i-=i&-i)res=max(res,t[i]);
        return res;
    }
};

void runcase(){
    int n,m;
    cin >> n >> m;
    Fenwick f(m+n+1);
    int ans=0;
    f.update(n,0);
    for(int i=2;i<=n;i++){
        for(int j=m/i*i;j>=i;j-=i){
            int x=j,c=0;
            while(x%i==0){
                c++;
                x/=i;
            }
            int v=f.query(j-i+n)+c;
            f.update(j-i+n,v);
            if(j+n-i<=m){
                ans=max(ans,v);
            }
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}