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

const int N=1e6+5;

int n,m;
vector<int> ch[2*N];
int fa[2*N],val[2*N];
int cnt[N];
ll ans;

int fp(int u){
    return fa[u]=u==fa[u]?u:fp(fa[u]);
}

int dfs(int u){
    if(u<=n)return cnt[u];
    int c=0;
    for(auto v:ch[u]){
        val[v]=min(val[v],val[u]);
        c+=dfs(v);
    }
    while(c>=2){
        ans+=val[u];
        c-=2;
    }
    return c;
}

void runcase(){
    cin >> n >> m;
    ans=0;
    for(int i=1;i<=2*n;i++){
        fa[i]=i;
    }
    int buf=n;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        cnt[u]^=1;
        cnt[v]^=1;
        u=fp(u),v=fp(v);
        if(u==v){
            val[u]=min(val[u],w);
        }else{
            buf++;
            fa[u]=buf;
            fa[v]=buf;
            ch[buf].emplace_back(u);
            ch[buf].emplace_back(v);
            val[buf]=w;
        }
        ans+=w;
    }
    assert(dfs(fp(1))==0);
    cout << ans << "\n";
    for(int i=1;i<=n;i++){
        cnt[i]=0;
    }
    for(int i=1;i<=2*n;i++){
        ch[i].clear();
        val[i]=0;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}