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
    int n;
    cin >> n;
    vector<int> p(n,-1);
    for(int i=1;i<n;i++){
        cin >> p[i];
        p[i]--;
    }
    using Info = pair<array<int,2>,pair<int,int>>;
    vector<array<int,2>> a(n,{0,0});
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[i][x]=1;
    }
    struct Cmp{
        bool operator()(const Info &l,const Info &r)const{
            return 1LL*l.first[0]*r.first[1]<1LL*r.first[0]*l.first[1];
        }
    };
    vector<int> ver(n);
    priority_queue<Info,vector<Info>,Cmp> pq;
    for(int i=1;i<n;i++){
        pq.emplace(a[i],make_pair(i,0));
    }
    vector<int> fa(n);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=(u==fa[u]?u:fp(fa[u]));
    };
    ll ans=0;
    while(!pq.empty()){
        auto [u,t]=pq.top().second;
        pq.pop();
        if(t<ver[u])continue;
        int v=fp(p[u]);
        ans+=1LL*a[v][1]*a[u][0];
        a[v][0]+=a[u][0];
        a[v][1]+=a[u][1];
        fa[u]=v;
        if(p[v]!=-1){
            pq.emplace(a[v],make_pair(v,++ver[v]));
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}