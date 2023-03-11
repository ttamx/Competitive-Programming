#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<tuple<int,int,int>> in;
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        in.push_back({x,y,i});
    }
    sort(in.begin(),in.end());
    vector<vector<int>> adj(n);
    stack<pair<int,int>> s;
    vector<int> rt;
    for(auto &[x,y,i]:in){
        while(!s.empty()&&s.top().first<y)s.pop();
        if(!s.empty())adj[s.top().second].push_back(i);
        else rt.push_back(i);
        s.push({y,i});
    }
    vector<int> p(n),r(n),d(n);
    function<void(int,int)> dfs=[&](int u,int pa){
        p[u]=pa;
        r[u]=r[pa];
        for(auto v:adj[u])dfs(v,u);
    };
    for(auto i:rt)r[i]=i,dfs(i,i);
    vector<int> q(m);
    vector<bool> req(n);
    map<int,vector<int>> mp;
    for(auto &x:q){
        cin >> x,x--;
        req[x]=true;
        mp[r[x]].push_back(x);
    }
    vector<bool> vis(n,0);
    vector<int> ans;
    for(auto [x,v]:mp){
        int cnt=v.size();
        function<void(int)> add=[&](int u){
            vis[u]=true;
            if(req[u])cnt--;
            for(auto v:adj[u])if(!vis[v])add(v);
        };
        int u=v[0];
        while(cnt){
            add(u);
            if(cnt)u=p[u];
        }
        ans.push_back(u);
    }
    sort(ans.begin(),ans.end());
    cout << ans.size() << '\n';
    for(auto i:ans)cout << i+1 << ' ';
}
