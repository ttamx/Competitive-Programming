#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> p(2*n+1),deg(2*n+1);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int x){return p[x]==x?x:p[x]=fp(p[x]);};
    auto uni=[&](int u,int v){
        u=fp(u);
        v=fp(v);
        if(u!=v)p[u]=v;
    };
    vector<vector<int>> adj(2*n+1);
    vector<bool> vis(2*n+1),used(n+1);
    for(int i=1;i<=n;i++)uni(i,i+n);
    for(int i=0;i<m;i++){
        int u,v;
        char a,b;
        cin >> u >> a >> v >> b;
        uni(u,v);
        if(a=='B')u+=n;
        if(b=='B')v+=n;
        deg[u]++;
        deg[v]++;
    }
    vector<bool> ok(2*n+1,1);
    for(int i=1;i<=2*n;i++){
        if(deg[i]==0)ok[fp(i)]=0;
    }
    int ans=0,all=0;
    for(int i=1;i<=2*n;i++){
        if(fp(i)!=i)continue;
        all++;
        ans+=ok[i];
    }
    cout << ans << ' ' << all-ans;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}