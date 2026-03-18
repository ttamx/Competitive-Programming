#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> adj(n);
    for(int i=0;i<m;i++){
        int k;
        cin >> k;
        vector<int> a(k);
        for(auto &x:a)cin >> x,x--;
        for(int j=0;j+1<k;j++){
            int u=a[j],v=a[j+1];
            adj[u].emplace_back(v);
            adj[v].emplace_back(u);
        }
    }
    vector<vector<vector<int>>> nodes(n,vector<vector<int>>(n));
    for(int i=0;i<n;i++){
        vector<int> dist(n,-1);
        queue<int> q;
        q.emplace(i);
        dist[i]=0;
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(dist[v]==-1){
                    dist[v]=dist[u]+1;
                    q.emplace(v);
                }
            }
        }
        for(int u=0;u<n;u++){
            for(auto v:adj[u]){
                if(dist[u]==dist[v]+1){
                    nodes[u][v].emplace_back(i);
                }
            }
        }
    }
    auto work=[&](){
        vector<bool> ok(n,true);
        while(count(ok.begin(),ok.end(),true)>1){
            pair<int,int> opt(n+1,-1);
            for(int u=0;u<n;u++){
                int mx=0;
                for(auto v:adj[u]){
                    int cnt=0;
                    for(auto x:nodes[u][v]){
                        if(ok[x]){
                            cnt++;
                        }
                    }
                    mx=max(mx,cnt);
                }
                opt=min(opt,make_pair(mx,u));
            }
            int u=opt.second;
            cout << u+1 << endl;
            string s;
            cin >> s;
            if(s[0]=='F')return;
            int v;
            cin >> v;
            v--;
            vector<bool> new_ok(n);
            for(auto x:nodes[u][v]){
                new_ok[x]=ok[x];
            }
            ok=move(new_ok);
        }
        int u=find(ok.begin(),ok.end(),true)-ok.begin();
        cout << u+1 << endl;
        string s;
        cin >> s;
        assert(s[0]=='F');
    };
    for(int i=0;i<n;i++)work();
}