#include "template.hpp"
#include "string/suffix-automaton.hpp"

void runcase(){
    string s;
    cin >> s;
    reverse(s.begin(),s.end());
    SuffixAutomaton sa(s);
    int n=sa.nodes.size();
    vector<int> a(n);
    vector<vector<int>> adj(n);
    for(int i=0;i<n;i++){
        a[i]=sa.nodes[i].len;
        int p=sa.nodes[i].link;
        if(p!=-1){
            adj[p].emplace_back(i);
            a[i]-=sa.nodes[p].len;
        }
    }
    a[0]=1;
    vector<int> dp(n,-1);
    function<int(int)> dfs=[&](int u){
        if(dp[u]!=-1)return dp[u];
        dp[u]=0;
        for(auto v:adj[u]){
            if(!dfs(v)){
                dp[u]=1;
            }
        }
        dp[u]^=(a[u]&1)^1;
        return dp[u];
    };
    cout << (dfs(0)?"Alice":"Bob") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}