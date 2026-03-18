#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/dsu.hpp"

using mint = mint107;

void runcase(){
    int n,m;
    cin >> n >> m;
    DSU dsu(m);
    vector<int> cyc(m);
    vector<int> ans;
    for(int i=0;i<n;i++){
        int k;
        cin >> k;
        if(k==1){
            int x;
            cin >> x;
            x--;
            x=dsu.find(x);
            if(!cyc[x]){
                cyc[x]=1;
                ans.emplace_back(i);
            }
        }else{
            int u,v;
            cin >> u >> v;
            u--,v--;
            u=dsu.find(u);
            v=dsu.find(v);
            if(u!=v&&!(cyc[u]&&cyc[v])){
                dsu.merge(u,v);
                cyc[u]|=cyc[v];
                ans.emplace_back(i);
            }
        }
    }
    mint pw=1;
    for(int i=0;i<ans.size();i++)pw*=2;
    cout << pw << " " << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}