#include<bits/stdc++.h>

using namespace std;

struct HopcroftKarp{
    int n,m;
    vector<int> match,lv,ptr;
    vector<vector<int>> adj;
    void init(int _n,int _m){
        n=_n,m=_m;
        adj.assign(n,vector<int>{});
    }
    void add_edge(int u,int v){
        adj[u].emplace_back(v+n);
    }
    void bfs(){
        lv.assign(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++){
            if(match[i]==-1){
                lv[i]=0;
                q.emplace(i);
            }
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                v=match[v];
                if(v!=-1&&lv[v]==-1){
                    lv[v]=lv[u]+1;
                    q.emplace(v);
                }
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(match[v]==-1||(lv[match[v]]==lv[u]+1&&dfs(match[v]))){
                match[u]=v;
                match[v]=u;
                return true;
            }
        }
        return false;
    }
    int max_matching(){
        match.assign(n+m,-1);
        int res=0,cnt;
        do{
            cnt=0;
            bfs();
            ptr.assign(n,0);
            for(int i=0;i<n;i++){
                if(match[i]==-1&&dfs(i)){
                    cnt++;
                }
            }
            res+=cnt;
        }while(cnt);
        return res;
    }
}bm;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n+2,vector<int>(m+2));
    for(int i=1;i<=n;i++){
        string s;
        cin >> s;
        for(int j=0;j<m;j++){
            a[i][j+1]=(s[j]=='B');
        }
    }
    for(int i=0;i<=n;i++){
        for(int j=0;j<=m;j++){
            a[i][j]^=a[i][j+1]^a[i+1][j]^a[i+1][j+1];
        }
    }
    int cnt=0;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cnt+=a[i][j];
        }
    }
    bm.init(n,m);
    for(int i=1;i<n;i++){
        for(int j=1;j<m;j++){
            if(a[i][j]&&a[i][m]&&a[n][j]){
                bm.add_edge(i,j);
            }
        }
    }
    int k=bm.max_matching();
    int ans=cnt;
    if(a[n][m])cnt--;
    for(int i=0;i<=k;i++){
        ans=min(ans,cnt-k+(a[n][m]+k)%2);
    }
    cout << ans << "\n";
}