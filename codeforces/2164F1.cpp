#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n),adj2(n),adj3(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> b;
    int buf=0;
    vector<int> pre(n,-1),nxt(n,-1);
    vector<int> ord(n);
    function<void(int)> dfs=[&](int u){
        int val=a[u];
        assert(b.size()>=val);
        b.insert(b.begin()+val,u);
        if(val>0){
            pre[u]=b[val-1];
        }
        if(val+1<b.size()){
            nxt[u]=b[val+1];
        }
        for(auto v:adj[u]){
            dfs(v);
        }
        b.erase(b.begin()+val);
        ord.emplace_back(u);
    };
    dfs(0);
    mint ans=1;
    map<pair<int,int>,int> ss;
    vector<int> sz(n);
    for(auto x:ord){
        int u=pre[x],v=nxt[x];
        if(u!=-1&&v!=-1){
            int s1=ss[{u,x}];
            int s2=ss[{x,v}];
            ans*=comb.fac(s1);
            ans*=comb.fac(s2);
            int s=s1+s2+1;
            ss[{u,v}]+=s;
            ans*=comb.ifac(s);
        }else if(u!=-1){
            int s=ss[{u,x}];
            ans*=comb.fac(s);
            sz[x]=s+1;
            adj2[u].emplace_back(x);
        }else if(v!=-1){
            int s=ss[{x,v}];
            ans*=comb.fac(s);
            sz[x]=s+1;
            adj3[v].emplace_back(x);
        }else{
            assert(x==0);
        }
    }
    function<int(int)> dfs2=[&](int u){
        int s=0;
        for(auto v:adj2[u]){
            int t=dfs2(v);
            ans*=comb.ifac(t);
            s+=t;
        }
        ans*=comb.fac(s);
        return s+sz[u];
    };
    dfs2(0);
    function<int(int)> dfs3=[&](int u){
        int s=0;
        for(auto v:adj3[u]){
            int t=dfs3(v);
            ans*=comb.ifac(t);
            s+=t;
        }
        ans*=comb.fac(s);
        return s+sz[u];
    };
    dfs3(0);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}