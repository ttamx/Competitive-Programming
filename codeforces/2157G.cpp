#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> memo(n+1,vector<int>(n+1,-2));
    vector<vector<int>> cost(n+1,vector<int>(n+1));
    vector<vector<int>> ans(n+1,vector<int>(n+1,-1));
    auto ask=[&](int l,int r){
        if(memo[l][r]!=-2)return memo[l][r];
        cost[l][r]=INF;
        cout << "? " << l+1 << " " << r << endl;
        cin >> memo[l][r];
        return memo[l][r];
    };
    for(int l=0;l<n;l++){
        for(int r=l+1;r<=n;r++){
            cost[l][r]=r-l;
        }
    }
    function<void(vector<int>,int)> rec=[&](vector<int> a,int d){
        if(a.empty()||d==-1)return;
        int m=a.size();
        vector<tuple<int,int,int>> e;
        for(int i=0;i<m;i++){
            for(int j=i+1;j<m;j++){
                e.emplace_back(cost[a[i]][a[j]],i,j);
            }
        }
        sort(e.rbegin(),e.rend());
        DSU dsu(m);
        vector<vector<pair<int,int>>> adj(m);
        for(auto [w,u,v]:e){
            if(dsu.merge(u,v)){
                int x=ask(a[u],a[v]);
                adj[u].emplace_back(v,x==d);
                adj[v].emplace_back(u,x==d);
            }
        }
        queue<int> q;
        vector<int> col(m,-1);
        col[0]=0;
        q.emplace(0);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto [v,w]:adj[u]){
                if(col[v]==-1){
                    col[v]=col[u]^w;
                    q.emplace(v);
                }
            }
        }
        vector<int> l,r;
        for(int i=0;i<m;i++){
            (col[i]?l:r).emplace_back(a[i]);
        }
        for(auto u:l){
            for(auto v:r){
                ans[u][v]=ans[v][u]=d;
            }
        }
        rec(l,d-1);
        rec(r,d-1);
    };
    vector<int> a(n+1);
    iota(a.begin(),a.end(),0);
    rec(a,29);
    cout << "!" << endl;
    for(int l=0;l<n;l++){
        for(int r=l+1;r<=n;r++){
            cout << ans[l][r] << " ";
        }
        cout << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}