#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    if(s=="prepare"){
        int n;
        cin >> n;
        vector<vector<int>> adj(n);
        for(int i=0;i<n-1;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
        vector<int> match(n,-1);
        function<bool(int,int)> dfs=[&](int u,int p){
            bool ok=true;
            for(auto v:adj[u])if(v!=p){
                if(dfs(v,u)&&ok){
                    match[u]=v;
                    ok=false;
                }
            }
            return ok;
        };
        dfs(n-1,-1);
        vector<int> col(n);
        function<void(int,int)> dfs2=[&](int u,int p){
            for(auto v:adj[u])if(v!=p){
                col[v]=col[u]^(v==match[u])^1;
                dfs2(v,u);
            }
        };
        dfs2(n-1,-1);
        for(int i=0;i<n-1;i++)cout << col[i];
        cout << endl;
    }else{
        int n;
        cin >> n;
        string s;
        cin >> s;
        s.push_back('0');
        for(int i=0;i<n-1;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            cout << (s[u]==s[v]?"take":"ignore") << endl;
        }
    }
}