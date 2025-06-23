#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
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
    vector<tuple<int,int,int>> ans;
    vector<int> sz(n);
    vector<bool> used(n);
    function<pair<int,int>(int)> decom=[&](int u)->pair<int,int> {
        vector<int> centroid;
        function<int(int,int)> dfs=[&](int u,int p){
            sz[u]=1;
            for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs(v,u);
            return sz[u];
        };
        int tot=dfs(u,-1);
        function<void(int,int)> dfs2=[&](int u,int p){
            for(auto v:adj[u])if(v!=p&&!used[v]){
                if(sz[v]*2>tot){
                    dfs2(v,u);
                    return;
                }
            }
            centroid.emplace_back(u);
            for(auto v:adj[u])if(v!=p&&!used[v]){
                if(sz[v]*2==tot){
                    centroid.emplace_back(v);
                }
            }
        };
        dfs(u,-1);
        dfs2(u,-1);
        for(auto c:centroid)used[c]=true;
        assert(centroid.size()<=2);
        pair<int,int> res(-1,-1);
        for(auto c:centroid){
            int cur=1;
            for(auto v:adj[c]){
                if(!used[v]){
                    auto [s,x]=decom(v);
                    cur+=s;
                    if(v!=x){
                        ans.emplace_back(c,v,x);
                    }
                }
            }
            res=max(res,{cur,c});
        }
        res.first=tot;
        return res;
    };
    decom(0);
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(auto [x,y,z]:ans){
        cout << x+1 << " " << y+1 << " " << z+1 << "\n";
    }
}