#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "data-structure/dsu.hpp"

using mint = mint998;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<string> s(n);
    for(auto &x:s)cin >> x;
    DSU dsu(4*n*m);
    auto enc=[&](int i,int j){return (i*m+j)*2;};
    int o=2*n*m;
    auto link=[&](int u,int v,bool f){
        dsu.merge(u,v+(f?o:0));
        dsu.merge(u+o,v+(f?0:o));
    };
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int u=enc(i,j);
            if(s[i][j]=='A'){
                {
                    int v=enc((i+1)%n,j);
                    if(s[(i+1)%n][j]=='A')link(u,v,true);
                    else link(u,v,true);
                }
                {
                    int v=enc(i,(j+1)%m);
                    if(s[i][(j+1)%m]=='A')link(u+1,v+1,true);
                    else link(u+1,v,false);
                }
            }else{
                {
                    int v=enc((i+1)%n,j);
                    if(s[(i+1)%n][j]=='A')link(u,v,false);
                    else link(u,v,false);
                }
                {
                    int v=enc(i,(j+1)%m);
                    if(s[i][(j+1)%m]=='A')link(u,v+1,true);
                    else link(u,v,false);
                }
            }
        }
    }
    for(int i=0;i<o;i++)if(dsu.same(i,i+o))return void(cout << 0 << "\n");
    mint ans=1;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int u=enc(i,j);
            if(dsu.find(u)==u)ans*=2;
            if(s[i][j]=='A'&&dsu.find(u+1)==u+1)ans*=2;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}