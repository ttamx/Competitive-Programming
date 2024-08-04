#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,q;
    cin >> n >> m >> q;
    vector<array<int,3>> a(n);
    for(auto &[x,y,z]:a)cin >> x >> y >> z;
    vector<vector<pair<int,double>>> adj(n);
    auto calc=[&](int u,int v){
        double res=0;
        for(int i=0;i<3;i++){
            int x=a[u][i]-a[v][i];
            res+=x*x;
        }
        return sqrt(res);
    };
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        double w=sqrt(calc(u,v));
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    using P = pair<double,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    vector<double> dist(n,1e100);
    vector<bool> vis(n,false);
    pq.emplace(0,0);
    dist[0]=0;
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        if(vis[u])continue;
        vis[u]=true;
        for(auto [v,w]:adj[u]){
            if(d+w<dist[v]){
                dist[v]=d+w;
                pq.emplace(dist[v],v);
            }
        }
    }
    cout << fixed << setprecision(12);
    while(q--){
        int x,t;
        cin >> x >> t;
        x--;
        double d=dist[x];
        double v=double(t)/d;
        if(v<2){
            cout << "impossible\n";
        }else{
            double c=v-sqrt(v*v-4);
            cout << c*d << "\n";
        }
    }
}