#include<bits/stdc++.h>

using namespace std;

const int N=505;

int n,m;
bool a[N][N];
int fa[N];
vector<pair<int,int>> edges;
vector<int> nodes;
vector<int> adj[2*N];
int match[2*N];
bool vis[2*N];
int grp[N],lab[N];
int val[N];

int fp(int u){return fa[u]=fa[u]==u?u:fp(fa[u]);}
void uni(int u,int v){fa[fp(u)]=fp(v);}

bool kuhn(int u){
    if(vis[u])return false;
    vis[u]=true;
    for(auto v:adj[u]){
        if(!match[v]||kuhn(match[v])){
            match[v]=u;
            match[u]=v;
            return true;
        }
    }
    return false;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=1;j<=m;j++)a[i][j]=(s[j-1]=='1');
    }
    iota(fa+1,fa+m+1,1);
    for(int i=1;i<=m;i++){
        for(int j=i+1;j<=m;j++){
            bool ij=true,ji=true;
            for(int k=1;k<=n;k++){
                if(a[k][i]&&!a[k][j])ij=false;
                if(!a[k][i]&&a[k][j])ji=false;
            }
            if(ij&&ji)uni(i,j);
            else if(ij)edges.emplace_back(i,j);
            else if(ji)edges.emplace_back(j,i);
        }
    }
    for(auto &[u,v]:edges)u=fp(u),v=fp(v);
    sort(edges.begin(),edges.end());
    edges.erase(unique(edges.begin(),edges.end()),edges.end());
    for(int i=1;i<=m;i++)if(i==fp(i))nodes.emplace_back(i);
    for(auto [u,v]:edges){
        v+=m;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    int cnt=0;
    for(auto u:nodes){
        for(int i=1;i<=2*m;i++)vis[i]=false;
        if(kuhn(u))cnt++;
    }
    int k=nodes.size()-cnt;
    int cg=0;
    for(auto u:nodes){
        if(!match[u+m]){
            cg++;
            int cur=1000;
            for(;u>0;u=match[u]-m){
                grp[u]=cg;
                lab[u]=cur--;
            }
        }
    }
    cout << k << "\n";
    for(int i=1;i<=m;i++)cout << grp[fp(i)] << " \n"[i==m];
    for(int i=1;i<=m;i++)cout << lab[fp(i)] << " \n"[i==m];
    for(int i=1;i<=n;i++){
        for(int i=1;i<=k;i++)val[i]=1;
        for(int j=1;j<=m;j++)if(a[i][j]){
            int g=grp[fp(j)];
            val[g]=max(val[g],lab[fp(j)]);
        }
        for(int j=1;j<=k;j++)cout << val[j] << " \n"[j==k];
    }
}