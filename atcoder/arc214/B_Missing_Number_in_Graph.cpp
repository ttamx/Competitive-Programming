#include "template.hpp"
#include "data-structure/binary-trie.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        u--,v--;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> val(n,-1);
    function<void(int)> dfs=[&](int u){
        for(auto [v,w]:adj[u]){
            if(val[v]==-1){
                val[v]=val[u]^w;
                dfs(v);
            }else{
                assert(val[v]==(val[u]^w));
            }
        }
    };
    val[0]=0;
    dfs(0);
    set<int> s;
    BinaryTrie<18> t;
    for(auto x:val)t.insert(x);
    for(int i=0;i<=n;i++){
        if(t.max(i)>n)continue;
        int l=0,r=n;
        while(l<r){
            int m=(l+r)/2;
            if(t.kth(m,i)>m)r=m;
            else l=m+1;
        }
        s.emplace(l);
    }
    if(s.size()==1){
        cout << *s.begin() << "\n";
    }else{
        cout << -1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}