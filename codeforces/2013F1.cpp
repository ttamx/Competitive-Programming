#include<bits/stdc++.h>

using namespace std;

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

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<int> par(n,-1);
    function<void(int,int)> dfs=[&](int u,int p){
        for(auto v:adj[u]){
            if(v!=p){
                par[v]=u;
                dfs(v,u);
            }
        }
    };
    int st;
    cin >> st >> st;
    st--;
    dfs(0,-1);
    vector<int> path;
    vector<bool> on_path(n);
    for(int u=st;u!=-1;u=par[u]){
        path.emplace_back(u);
        on_path[u]=true;
    }
    reverse(path.begin(),path.end());
    int m=path.size();
    vector<int> dep(m);
    function<int(int,int)> get_dep=[&](int u,int p){
        int res=0;
        for(auto v:adj[u]){
            if(v!=p){
                res=max(res,get_dep(v,u));
            }
        }
        return res+1;
    };
    for(int i=0;i<m;i++){
        int u=path[i];
        for(auto v:adj[u]){
            if(!on_path[v]){
                dep[i]=max(dep[i],get_dep(v,u));
            }
        }
        dep[i]++;
    }
    auto dpa=dep;
    auto dpb=dep;
    for(int i=0;i<m;i++){
        dpa[i]+=i;
        dpb[i]+=m-i-1;
    }
    multiset<int> msa,msb;
    for(int i=0;i<m;i++){
        msa.emplace(dpa[i]);
        msb.emplace(dpb[i]);
    }
    int mna=m,mnb=m;
    for(int i=0;i<m;i++){
        msb.erase(msb.find(dpb[i]));
        if(msb.empty())break;
        if(i>0)msb.erase(msb.find(dpb[m-i]));
        if(msb.empty())break;
        if(dpa[i]>*msb.rbegin()){
            mna=i;
            break;
        }
    }
    for(int i=m-1;i>=0;i--){
        msa.erase(msa.find(dpa[i]));
        if(msa.empty())break;
        msa.erase(msa.find(dpa[m-i-1]));
        if(msa.empty())break;
        if(dpb[i]>=*msa.rbegin()){
            mnb=m-i-1;
            break;
        }
    }
    if(mna==m&&mnb==m){
        int l=0,r=m-1;
        while(l+1<r){
            l++;
            if(l+1<r)r--;
        }
        cout << (dpa[l]>dpb[r]?"Alice":"Bob") << "\n";
    }else{
        cout << (mna<=mnb?"Alice":"Bob") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}