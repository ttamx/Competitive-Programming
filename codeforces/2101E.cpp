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
    string s;
    cin >> s;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int lg=0;
    while((1<<lg)<n)lg++;
    vector<int> sz(n),cp(n),lv(n);
    vector<bool> used(n);
    vector<vector<int>> dist(lg,vector<int>(n,-1));
    function<int(int,int)> get_sz=[&](int u,int p)->int {
        sz[u]=1;
        for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
        return sz[u];
    };
    function<int(int,int,int)> centroid=[&](int u,int p,int cnt)->int {
        for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,u,cnt);
        return u;
    };
    function<void(int,int,int)> decom=[&](int u,int p,int l){
        u=centroid(u,-1,get_sz(u,-1));
        cp[u]=p;
        lv[u]=l;
        queue<pair<int,int>> q;
        q.emplace(u,dist[l][u]=0);
        while(!q.empty()){
            auto [v,d]=q.front();
            q.pop();
            for(auto x:adj[v])if(!used[x]&&dist[l][x]==-1)q.emplace(x,dist[l][x]=d+1);
        }
        used[u]=true;
        for(auto v:adj[u])if(!used[v])decom(v,u,l+1);
    };
    vector<vector<pair<int,int>>> dp(n);
    auto upd=[&](vector<pair<int,int>> &a,int v,int id){
        for(int i=0;i<=a.size();i++){
            if(i==a.size()||v>=a[i].first){
                a.insert(a.begin()+i,make_pair(v,id));
                break;
            }
        }
        int cnt=0;
        int last=-1;
        for(int i=0;i<a.size();i++)if(a[i].second==id){
            cnt++;
            last=i;
        }
        if(cnt>lg)a.erase(a.begin()+last);
        if(a.size()>lg*2)a.pop_back();
    };
    vector<vector<int>> dp2(n);
    auto upd2=[&](vector<int> &a,int v){
        for(int i=0;i<=a.size();i++){
            if(i==a.size()||v>=a[i]){
                a.insert(a.begin()+i,v);
                break;
            }
        }
        if(a.size()>lg)a.pop_back();
    };
    decom(0,-1,0);
    for(int i=0;i<n;i++)if(s[i]=='1'){
        int u=i,c=-1;
        for(;u!=-1;u=cp[u]){
            upd(dp[u],dist[lv[u]][i],c);
            c=u;
        }
    }
    for(int i=0;i<n;i++)if(s[i]=='1'){
        int u=i,c=-1;
        for(;u!=-1;u=cp[u]){
            for(auto [x,id]:dp[u]){
                if(id!=c){
                    upd2(dp2[i],dist[lv[u]][i]);
                }
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}