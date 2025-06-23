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

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    vector<pair<int,int>> b(m);
    for(auto &[l,r]:b)cin >> l >> r;
    sort(b.begin(),b.end(),[&](pii x,pii y){
        return x.second<y.second||(x.second==y.second&&x.first>y.first);
    });
    vector<tuple<ll,ll,int>> c;
    for(auto [l,r]:b){
        auto it=lower_bound(a.begin(),a.end(),l);
        if(it!=a.end()&&*it<=r)continue;
        if(!c.empty()&&l<=get<0>(c.back()))continue;
        c.emplace_back(l,r,0);
    }
    c.emplace_back(-LINF,-LINF,1);
    for(auto x:a){
        c.emplace_back(x,x,1);
    }
    sort(c.begin(),c.end());
    n=c.size();
    vector<array<ll,2>> dpl(n,{LINF,LINF}),dpr(n,{LINF,LINF});
    dpl[0][0]=dpl[0][1]=0LL;
    for(int i=1;i<n;i++){
        auto [l,r,t]=c[i];
        auto [pl,pr,pt]=c[i-1];
        if(t){
            dpl[i][0]=min({dpl[i-1][0],dpl[i-1][1],dpr[i-1][1]+(l-pr)*2});
            dpl[i][1]=min({dpl[i-1][0],dpl[i-1][1],dpr[i-1][0]+(l-pr)});
            dpr[i][0]=dpr[i][1]=min({dpl[i-1][0],dpl[i-1][1],dpr[i-1][0]+(l-pr),dpr[i-1][1]+(l-pr)*2});
        }else{
            dpl[i][0]=dpl[i-1][0]+(l-pl);
            dpl[i][1]=dpl[i-1][1]+(l-pl)*2;
            ll c=min(dpl[i-1][0],dpl[i-1][1]);
            dpr[i][0]=min(c,dpr[i-1][0]+(r-pr));
            dpr[i][1]=min(c,dpr[i-1][1]+(r-pr)*2);
        }
    }
    cout << min(dpl[n-1][0],dpl[n-1][1]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}