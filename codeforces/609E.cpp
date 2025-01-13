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
    vector<tuple<int,int,int>> edges(m);
    for(auto &[u,v,w]:edges){
        cin >> u >> v >> w;
        u--,v--;
    }
    vector<int> fa(n),ord(m);
    iota(fa.begin(),fa.end(),0);
    iota(ord.begin(),ord.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    auto merge=[&](int u,int v)->bool {
        u=fp(u),v=fp(v);
        if(u==v)return false;
        return fa[u]=v,true;
    };
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return get<2>(edges[i])<get<2>(edges[j]);
    });
    vector<int> mst,nonmst;
    ll base=0;
    for(auto i:ord){
        auto [u,v,w]=edges[i];
        if(merge(u,v)){
            base+=w;
            mst.emplace_back(i);
        }else{
            nonmst.emplace_back(i);
        }
    }
    vector<int> l(m-n+1),r(m-n+1,n-1);
    while(true){
        vector<vector<int>> qr(n-1);
        bool done=true;
        for(int i=0;i<m-n+1;i++){
            if(l[i]!=r[i]){
                done=false;
                qr[(l[i]+r[i])/2].emplace_back(i);
            }
        }
        if(done)break;
        iota(fa.begin(),fa.end(),0);
        for(int i=0;i<n-1;i++){
            auto [u,v,w]=edges[mst[i]];
            merge(u,v);
            for(auto j:qr[i]){
                auto [uu,vv,ww]=edges[nonmst[j]];
                if(fp(uu)==fp(vv)){
                    r[j]=i;
                }else{
                    l[j]=i+1;
                }
            }
        }
    }
    vector<ll> ans(m,base);
    for(int i=0;i<m-n+1;i++){
        ans[nonmst[i]]=base-get<2>(edges[mst[l[i]]])+get<2>(edges[nonmst[i]]);
    }
    for(auto x:ans){
        cout << x << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}