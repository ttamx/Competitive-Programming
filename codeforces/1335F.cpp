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
    vector<int> a(n*m),nxt(n*m);
    vector<vector<int>> adj(n*m);
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++)a[i*m+j]=s[j]=='1';
    }
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            int u=i*m+j;
            int v=u;
            if(s[j]=='U')v-=m;
            if(s[j]=='D')v+=m;
            if(s[j]=='R')v++;
            if(s[j]=='L')v--;
            nxt[u]=v;
            adj[v].emplace_back(u);
        }
    }
    int cycle;
    vector<bool> vis(n*m),mark;
    function<void(int,int)> dfs=[&](int u,int c){
        if(vis[u])return;
        vis[u]=true;
        if(!a[u])mark[c]=true;
        for(auto v:adj[u])dfs(v,(c+1)%cycle);
    };
    int ans1=0,ans2=0;
    vector<int> id(n*m,-1);
    for(int i=0;i<n*m;i++){
        int j=i;
        while(id[j]==-1){
            id[j]=i;
            j=nxt[j];
        }
        if(id[j]!=i)continue;
        int k=j;
        cycle=1;
        while(nxt[k]!=j){
            cycle++;
            k=nxt[k];
        }
        mark.assign(cycle,false);
        dfs(j,0);
        ans1+=cycle;
        ans2+=count(mark.begin(),mark.end(),true);
    }
    cout << ans1 << " " << ans2 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}