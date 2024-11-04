#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

struct Trie{
    struct Node{
        array<int,26> adj;
        Node(){
            for(int i=0;i<26;i++){
                adj[i]=-1;
            }
        }
    };
    vector<Node> nodes;
    vector<bool> lazy;
    int root;
    Trie():nodes(0),root(new_node(false)){}
    int new_node(bool lz){
        nodes.emplace_back(Node());
        lazy.emplace_back(lz);
        return nodes.size()-1;
    }
    int copy_node(int i,bool lz){
        if(i==-1)return new_node(lz);
        nodes.emplace_back(nodes[i]);
        lazy.emplace_back(lz);
        return nodes.size()-1;
    }
    void insert(const string &s){
        int n=s.size();
        vector<int> cur{root};
        for(int i=0;i<s.size();i++){
            vector<int> nxt;
            if(s[i]=='?'){
                int x=-1;
                for(auto u:cur){
                    for(int j=0;j<26;j++){
                        if(nodes[u].adj[j]!=-1){
                            if(lazy[nodes[u].adj[j]]){
                                nodes[u].adj[j]=copy_node(nodes[u].adj[j],false);
                            }
                            nxt.emplace_back(nodes[u].adj[j]);
                        }else{
                            if(x==-1){
                                x=new_node(true);
                                nxt.emplace_back(x);
                            }
                            nodes[u].adj[j]=x;
                        }
                    }
                }
            }else{
                int c=s[i]-'A';
                for(auto u:cur){
                    if(nodes[u].adj[c]==-1||lazy[nodes[u].adj[c]]){
                        cerr << nodes[u].adj[c]-1 << " ";
                        nodes[u].adj[c]=copy_node(nodes[u].adj[c],false);
                    }
                    nxt.emplace_back(nodes[u].adj[c]);
                }
            }
            swap(cur,nxt);
        }
        cerr << "\n----\n";
    }
    mint solve(){
        int n=nodes.size();
        vector<mint> dp(n);
        dp[0]=1;
        mint res=0;
        for(int i=0;i<n;i++){
            cerr << dp[i] << " ";
            res+=dp[i];
            for(auto j:nodes[i].adj){
                if(j!=-1){
                    dp[j]+=dp[i];
                }
            }
        }
        cerr << "\n";
        return res;
    }
};

void runcase(){
    int n;
    cin >> n;
    Trie t;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        t.insert(s);
    }
    cout << t.solve() << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}