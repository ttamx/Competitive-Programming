#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,q,m;
vector<tuple<int,int,int>> qr[N];
int val[N];
vector<int> adj[N];
int timer=0;
int ans[N];

struct Trie{
    struct Node{
        int t;
        array<int,2> ch;
        Node():t(N),ch{-1,-1}{}
    };
    vector<Node> node;
    vector<pair<int,int>> dat;
    Trie():dat(){new_node();}
    int new_node(){
        node.emplace_back(Node());
        return node.size()-1;
    }
    int get_t(int u){
        return ~u?node[u].t:N;
    }
    void update(int x,int t){
        dat.emplace_back(x,t);
        int u=0;
        node[u].t=min(node[u].t,t);
        for(int i=29;i>=0;i--){
            int c=x>>i&1;
            if(node[u].ch[c]==-1)node[u].ch[c]=new_node();
            u=node[u].ch[c];
            node[u].t=min(node[u].t,t);
        }
    }
    int query(int x,int t){
        int res=0;
        int u=0;
        for(int i=29;i>=0;i--){
            int c=x>>i&1;
            if(get_t(node[u].ch[c^1])<=t){
                u=node[u].ch[c^1];
                res|=1<<i;
            }else{
                u=node[u].ch[c];
            }
        }
        return res;
    }
    int size(){
        return dat.size();
    }
    void clear(){
        node.clear();
        dat.clear();
    }
}dp[N];

void dfs(int u){
    dp[u].update(val[u],u);
    for(auto v:adj[u]){
        dfs(v);
        if(dp[v].size()>dp[u].size())swap(dp[u],dp[v]);
        for(auto [x,t]:dp[v].dat){
            dp[u].update(x,t);
        }
        dp[v].clear();
    }
    for(auto [x,t,i]:qr[u]){
        ans[i]=dp[u].query(x,t);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> q;
    n=1;
    for(int i=1;i<=q;i++){
        string op;
        int x,y;
        cin >> op >> x >> y;
        if(op=="Add"){
            val[++n]=val[x]^y;
            adj[x].emplace_back(n);
        }else{
            qr[y].emplace_back(val[x],n,++m);
        }
    }
    dfs(1);
    for(int i=1;i<=m;i++){
        cout << ans[i] << "\n";
    }
}