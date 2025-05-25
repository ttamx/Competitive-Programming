#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "modular-arithmetic/combinatorics.hpp"

using mint = mint998;

Combinatorics<mint> comb;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<pair<int,int>> a(m);
    bool ok=false;
    for(auto &[l,r]:a){
        cin >> l >> r;
        if(l==1&&r==n){
            ok=true;
        }
    }
    if(!ok){
        a.emplace_back(1,n);
        m++;
    }
    sort(a.begin(),a.end(),[&](pair<int,int> x,pair<int,int> y){
        return x.first<y.first||(x.first==y.first&&x.second>y.second);
    });
    vector<vector<int>> adj(m);
    stack<int> s;
    s.emplace(0);
    for(int i=1;i<m;i++){
        while(a[s.top()].second<a[i].first){
            s.pop();
        }
        adj[s.top()].emplace_back(i);
        s.emplace(i);
    }
    vector<mint> pw(n+1);
    pw[0]=1;
    for(int i=1;i<=n;i++){
        pw[i]=pw[i-1]*2;
    }
    int idx=0;
    function<mint(int)> dfs=[&](int u)->mint {
        auto [l,r]=a[u];
        if(l==r)return 1;
        int cur=r-l;
        for(auto v:adj[u]){
            auto [l2,r2]=a[v];
            if(l2<r2){
                cur-=r2-l2;
            }
        }
        mint res=comb.C(cur*2,cur)/(cur+1);
        for(auto v:adj[u]){
            res*=dfs(v);
        }
        return res;
    };
    cout << dfs(0) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}