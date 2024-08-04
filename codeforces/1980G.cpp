#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> d(n),dep(n);
    BinaryTrie<30> trie[2];
    function<void(int,int)> dfs=[&](int u,int p){
        trie[dep[u]].insert(d[u]);
        for(auto [v,w]:adj[u])if(v!=p){
            d[v]=d[u]^w;
            dep[v]=dep[u]^1;
            dfs(v,u);
        }
    };
    dfs(0,0);
    int sum=0;
    while(q--){
        char op;
        cin >> op;
        if(op=='^'){
            int x;
            cin >> x;
            sum^=x;
        }else{
            int v,x;
            cin >> v >> x;
            v--;
            trie[dep[v]].erase(d[v]);
            uint32_t ans=0;
            if(!trie[dep[v]].empty()){
                ans=max(ans,trie[dep[v]].max(d[v]^x));
            }
            if(!trie[dep[v]^1].empty()){
                ans=max(ans,trie[dep[v]^1].max(d[v]^x^sum));
            }
            trie[dep[v]].insert(d[v]);
            cout << ans << " ";
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}