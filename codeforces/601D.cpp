#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;

int n,ans,cnt;
int c[N],ch[N][26],sz[N];
string s;
basic_string<int> adj[N];

int merge(int x,int y){
    if(!x||!y)return x|y;
    sz[x]=1;
    for(int i=0;i<26;i++)sz[x]+=sz[ch[x][i]=merge(ch[x][i],ch[y][i])];
    return x;
}

void dfs(int u,int p){
    for(auto v:adj[u])if(v!=p)dfs(v,u),ch[u][s[v]-'a']=merge(ch[u][s[v]-'a'],v);
    sz[u]=1;
    for(int i=0;i<26;i++)sz[u]+=sz[ch[u][i]];
    int x=c[u]+sz[u];
    if(x>ans)ans=x,cnt=1;
    else if(x==ans)cnt++;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> c[i];
    cin >> s,s=" "+s;
    for(int i=0,u,v;i<n-1;i++)cin >> u >> v,adj[u]+=v,adj[v]+=u;
    dfs(1,0);
    cout << ans << "\n" << cnt << "\n";
}