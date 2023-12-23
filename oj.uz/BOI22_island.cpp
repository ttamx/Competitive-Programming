#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

typedef pair<int,int> p2;
typedef tuple<int,int,int> t3;

const int N=2e5+5;

int n,m;
int s[2*N],fa[2*N],ans[2*N];
ll sz[2*N];
vector<t3> edge;
vector<p2> node;

int fp(int u){
    if(u==fa[u])return u;
    return fa[u]=fp(fa[u]);
}

void dfs(int u){
    if(u<=n)return;
    auto [l,r]=node[u];
    if(ans[u]==0)ans[l]=ans[r]=0;
    dfs(l);
    dfs(r);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> s[i];
    for(int i=1;i<=2*n;i++){
        fa[i]=i;
        sz[i]=s[i];
        ans[i]=1;
    }
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        edge.emplace_back(max(s[u],s[v]),u,v);
    }
    sort(edge.begin(),edge.end());
    node=vector<p2>(n+1,p2(0,0));
    for(auto [w,u,v]:edge){
        int pu=fp(u),pv=fp(v);
        if(pu==pv)continue;
        if(sz[pu]<w)ans[pu]=0;
        if(sz[pv]<w)ans[pv]=0;
        int p=node.size();
        node.emplace_back(pu,pv);
        fa[pu]=fa[pv]=p;
        sz[p]=sz[pu]+sz[pv];
    }
    for(int i=2;i<=n;i++)if(fp(i)!=fp(1))cout << string(n,'0'),exit(0);
    dfs(node.size()-1);
    for(int i=1;i<=n;i++)cout << ans[i];
}