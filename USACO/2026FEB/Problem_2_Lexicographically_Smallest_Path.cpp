#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<pair<int,char>>> adj(n);
    vector<char> mn(n,'z');
    for(int i=0;i<m;i++){
        int u,v;
        char c;
        cin >> u >> v >> c;
        u--,v--;
        adj[u].emplace_back(v,c);
        adj[v].emplace_back(u,c);
    }
    vector<int> dist(n,-1);
    dist[0]=0;
    vector<char> ch(n,'z'+1);
    ch[0]='a';
    vector<int> q{0};
    vector<bool> mark(n);
    char cur='z';
    for(int i=0;i<n;i++){
        vector<int> nq,nnq;
        for(auto u:q){
            for(auto [v,w]:adj[u]){
                cur=min(cur,w);
                if(w>=ch[v])continue;
                ch[v]=w;
                if(mark[v])continue;
                mark[v]=true;
                nq.emplace_back(v);
            }
        }
        for(auto u:nq){
            mark[u]=false;
            if(ch[u]!=cur)continue;
            nnq.emplace_back(u);
            if(dist[u]==-1)dist[u]=i+1;
        }
        q=move(nnq);
    }
    for(int i=0;i<n;i++)cout << dist[i] << " \n"[i==n-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}