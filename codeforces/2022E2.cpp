#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint107;

void runcase(){
    int n,m,k,q;
    cin >> n >> m >> k >> q;
    mint base=mint(1<<30);
    vector<mint> pw(n+m);
    pw[0]=1;
    for(int i=1;i<n+m;i++){
        pw[i]=pw[i-1]*base;
    }
    int cnt=n+m-1;
    vector<int> p(n+m),sz(n+m,1),e(n+m);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]==u?u:fp(p[u]);
    };
    function<int(int)> getval=[&](int u){
        return p[u]==u?0:(getval(p[u])^e[u]);
    };
    bool ok=true;
    auto update=[&](int u,int v,int w){
        if(!ok)return;
        int pu=fp(u),pv=fp(v);
        if(pu==pv){
            if((getval(u)^getval(v))!=w){
                ok=false;
            }
            return;
        }
        if(sz[pu]<sz[pv]){
            swap(u,v);
            swap(pu,pv);
        }
        p[pv]=pu;
        sz[pu]+=sz[pv];
        e[pv]=getval(u)^getval(v)^w;
        cnt--;
    };
    auto answer=[&](){
        cout << (ok?pw[cnt]:mint(0)) << "\n";
    };
    while(k--){
        int i,j,v;
        cin >> i >> j >> v;
        i--,j--;
        update(i,j+n,v);
    }
    answer();
    while(q--){
        int i,j,v;
        cin >> i >> j >> v;
        i--,j--;
        update(i,j+n,v);
        answer();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}