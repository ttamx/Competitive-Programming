#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    auto g=read_tree(n);
    HLD hld(g);
    auto ord=hld.ord;
    reverse(ord.begin(),ord.end());
    vector<vector<mint>> dp(n,vector<mint>(n));
    vector<vector<mint>> aux(n,vector<mint>(n));
    vector<vector<mint>> aux2(n,vector<mint>(n));
    for(auto u:ord){
        for(auto v:ord){
            if(s[u]==s[v]){
                dp[u][v]++;
                for(auto uu:g[u])if(uu!=hld.par[u]){
                    dp[u][v]+=aux2[uu][v];
                }
            }
            for(auto vv:g[v])if(vv!=hld.par[v]){
                aux[u][v]+=aux[u][vv]+dp[u][vv];
            }
            aux2[u][v]+=aux[u][v];
            for(auto uu:g[u])if(uu!=hld.par[u]){
                aux2[u][v]+=aux2[uu][v];
            }
        }
    }
    for(auto u:ord){
        for(auto v:ord){
            for(auto vv:g[v])if(vv!=hld.par[v]){
                dp[u][v]+=dp[u][vv];
            }
        }
    }
    for(auto u:ord){
        for(auto v:ord){
            for(auto uu:g[u])if(uu!=hld.par[u]){
                dp[u][v]+=dp[uu][v];
            }
        }
    }
    for(int i=0;i<n;i++){
        cout << dp[i][i] << " \n"[i==n-1];
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}