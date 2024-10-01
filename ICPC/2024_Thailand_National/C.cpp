#include<bits/stdc++.h>

using namespace std;

struct HopcroftKarp{
    int n,m;
    vector<int> l,r,lv,ptr;
    vector<vector<int>> adj;
    HopcroftKarp(){}
    HopcroftKarp(int _n,int _m){init(_n,_m);}
    void init(int _n,int _m){
        n=_n,m=_m;
        adj.assign(n+m,vector<int>{});
    }
    void addEdge(int u,int v){
        adj[u].emplace_back(v+n);
    }
    void bfs(){
        lv=vector<int>(n,-1);
        queue<int> q;
        for(int i=0;i<n;i++)if(l[i]==-1){
            lv[i]=0;
            q.emplace(i);
        }
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(int v:adj[u])if(r[v]!=-1&&lv[r[v]]==-1){
                lv[r[v]]=lv[u]+1;
                q.emplace(r[v]);
            }
        }
    }
    bool dfs(int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            int v=adj[u][i];
            if(r[v]==-1||(lv[r[v]]==lv[u]+1&&dfs(r[v]))){
                l[u]=v,r[v]=u;
                return true;
            }
        }
        return false;
    }
    int maxMatching(){
        int match=0,cnt=0;
        l=r=vector<int>(n+m,-1);
        do{
            ptr=vector<int>(n);
            bfs();
            cnt=0;
            for(int i=0;i<n;i++)if(l[i]==-1&&dfs(i))cnt++;
            match+=cnt;
        }while(cnt);
        return match;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m));
    vector<int> vals;
    for(auto &v:a){
        for(auto &x:v){
            cin >> x;
            vals.emplace_back(x);
        }
    }
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    HopcroftKarp mbm;
    auto check=[&](int x){
        mbm.init(n,m);
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                if(a[i][j]>=x){
                    mbm.addEdge(i,j);
                }
            }
        }
        return mbm.maxMatching()==n;
    };
    int l=0,r=vals.size()-1;
    while(l<r){
        int m=(l+r+1)/2;
        if(check(vals[m]))l=m;
        else r=m-1;
    }
    check(vals[l]);
    cout << vals[l] << "\n";
    for(int i=0;i<n;i++)cout << mbm.l[i]-n+1 << " ";
}