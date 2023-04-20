#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n+1);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[v].emplace_back(u);
    }
    vector<int> disc(n+1);
    auto pre=[&]{
        int time=n;
        queue<int> q;
        vector<bool> vis(n+1);
        q.emplace(1);
        while(!q.empty()){
            auto u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(vis[v])continue;
                vis[v]=true;
                q.emplace(v);
                disc[v]=time--;
            }
        }
    };
    pre();
    vector<bool> used(n+1);
    vector<int> ans;
    int cnt=0;
    vector<int> vec;
    vec.emplace_back(1);
    used[1]=true;
    queue<int> q;
    while(!vec.empty()){
        vector<int> res;
        for(auto st:vec){
            vector<int> s;
            queue<int> q;
            vector<bool> vis(n+1);
            q.emplace(st);
            while(!q.empty()){
                int u=q.front();
                q.pop();
                if(u!=st)s.emplace_back(u);
                for(auto v:adj[u]){
                    if(vis[v]||used[v])continue;
                    vis[v]=true;
                    q.emplace(v);
                }
            }
            sort(s.begin(),s.end(),[&](int x,int y){
                return disc[x]<disc[y];
            });
            for(auto x:s){
                disc[x]=ans.size();
                ans.emplace_back(x);
            }
            ans.emplace_back(st);
            used[st]=true;
            cnt++;
            for(auto v:adj[st]){
                if(used[v])continue;
                used[v]=true;
                res.emplace_back(v);
            }
        }
        vec=res;
        sort(vec.begin(),vec.end(),[&](int x,int y){
            return disc[x]<disc[y];
        });
    }
    if(cnt<n){
        cout << "INFINITE\n";
        return;
    }
    cout << "FINITE\n";
    cout << ans.size() << '\n';
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}