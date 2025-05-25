
#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int dx[4]={-1,0,1,0};
int dy[4]={0,-1,0,1};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
        }
    }
    auto enc=[&](int i,int j){
        return i*m+j;
    };
    vector<int> fa(n*m);
    iota(fa.begin(),fa.end(),0);
    function<int(int)> fp=[&](int u){
        return fa[u]=u==fa[u]?u:fp(fa[u]);
    };
    vector<tuple<int,int,int>> seq;
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            seq.emplace_back(a[i][j],i,j);
        }
    }
    int lg=0;
    while((1<<lg)<n*m)lg++;
    lg++;
    vector<vector<int>> nxt(lg,vector<int>(n*m,-1));
    vector<vector<int>> par(lg,vector<int>(n*m,-1));
    vector<bool> alive(n*m);
    vector<int> b(n*m);
    vector<vector<int>> adj(n*m);
    sort(seq.begin(),seq.end());
    for(auto [val,i,j]:seq){
        int u=enc(i,j);
        alive[u]=true;
        b[u]=val;
        for(int d=0;d<4;d++){
            int ii=i+dx[d];
            int jj=j+dy[d];
            if(ii<0||ii>=n||jj<0||jj>=m)continue;
            int v=enc(ii,jj);
            if(!alive[v])continue;
            v=fp(v);
            if(v!=u){
                fa[v]=u;
                adj[u].emplace_back(v);
                par[0][v]=u;
            }
        }
    }
    int root=fp(0);
    par[0][root]=root;
    vector<int> dep(n*m);
    vector<pair<int,int>> path;
    function<void(int)> dfs=[&](int u){
        path.emplace_back(b[u],u);
        nxt[0][u]=prev(lower_bound(path.rbegin(),path.rend(),make_pair(b[u]+k+1,-1)))->second;
        for(auto v:adj[u]){
            dep[v]=dep[u]+1;
            dfs(v);
        }
        path.pop_back();
    };
    dfs(root);
    for(int i=1;i<lg;i++){
        for(int u=0;u<n*m;u++){
            par[i][u]=par[i-1][par[i-1][u]];
            nxt[i][u]=nxt[i-1][nxt[i-1][u]];
        }
    }
    auto lca=[&](int u,int v){
        if(dep[u]<dep[v])swap(u,v);
        for(int i=lg-1;i>=0;i--){
            int x=par[i][u];
            if(dep[x]>=dep[v])u=x;
        }
        if(u==v)return u;
        for(int i=lg-1;i>=0;i--){
            int x=par[i][u],y=par[i][v];
            if(x!=y)u=x,v=y;
        }
        return par[0][u];
    };
    auto get=[&](){
        int i,j;
        cin >> i >> j;
        i--,j--;
        return enc(i,j);
    };
    int q;
    cin >> q;
    while(q--){
        int u=get();
        int v=get();
        v=lca(u,v);
        int ans=0;
        for(int i=lg-1;i>=0;i--){
            int x=nxt[i][u];
            if(dep[x]>dep[v]){
                u=x;
                ans+=1<<i;
            }
        }
        u=nxt[0][u];
        ans++;
        cout << (dep[u]<=dep[v]?ans:-1) << "\n";
    }
}