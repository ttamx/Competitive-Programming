#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,b;
    cin >> n >> b;
    string s;
    cin >> s;
    vector<int> a;
    for(auto x:s)a.emplace_back(x=='R'?0:x=='G'?1:2);
    vector<vector<int>> id(n);
    for(int i=0;i<b;i++){
        int k;
        cin >> k;
        while(k--){
            int x;
            cin >> x;
            x--;
            id[x].emplace_back(i);
        }
    }
    vector<int> col(b,-1);
    for(int i=0;i<n;i++)if(id[i].empty()){
        if(a[i]!=0)cout << "impossible\n",exit(0);
    }
    for(int i=0;i<n;i++)if(id[i].size()==1){
        int j=id[i][0];
        int req=(3-a[i])%3;
        if(col[j]!=-1&&col[j]!=req)cout << "impossible\n",exit(0);
        col[j]=req;
    }
    vector<vector<pair<int,int>>> adj(b);
    for(int i=0;i<n;i++)if(id[i].size()==2){
        int u=id[i][0],v=id[i][1];
        int w=(3-a[i])%3;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    vector<int> comp;
    vector<bool> vis(b);
    function<void(int)> dfs=[&](int u){
        vis[u]=true;
        assert(col[u]!=-1);
        comp.emplace_back(u);
        for(auto [v,w]:adj[u]){
            if(col[v]==-1){
                col[v]=(3+w-col[u])%3;
            }
            if(!vis[v]){
                dfs(v);
            }
            if((col[u]+col[v])%3!=w)cout << "impossible\n",exit(0);
        }
    };
    for(int i=0;i<b;i++)if(col[i]!=-1&&!vis[i]){
        dfs(i);
        comp.clear();
    }
    for(int i=0;i<b;i++)if(col[i]==-1){
        pair<int,int> mn(INT_MAX,-1);
        for(int j=0;j<3;j++){
            col[i]=j;
            dfs(i);
            int res=0;
            for(auto x:comp)res+=col[x];
            for(auto x:comp){
                col[x]=-1;
                vis[x]=false;
            }
            mn=min(mn,{res,j});
            comp.clear();
        }
        col[i]=mn.second;
        dfs(i);
        comp.clear();
    }
    int ans=0;
    for(int i=0;i<b;i++){
        assert(col[i]!=-1);
        ans+=col[i];
    }
    cout << ans << "\n";
}