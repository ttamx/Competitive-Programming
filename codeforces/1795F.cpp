#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> adj(n+1);
    for(int i=1;i<n;i++){
        int u,v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    vector<int> q;
    vector<int> p(n+1,-1);
    q.push_back(1);
    p[1]=0;
    for(int i=0;i<n;i++){
        int u=q[i];
        for(auto v:adj[u]){
            if(p[v]!=-1)continue;
            p[v]=u;
            q.push_back(v);
        }
    }
    int k;
    cin >> k;
    vector<int> a(k);
    for(auto &x:a)cin >> x;
    int l=0,r=n;
    while(l<r){
        int m=(l+r+1)/2;
        bool ok=true;
        vector<int> dist(n+1,-1),below(n+1,0);
        for(int i=0;i<k;i++)dist[a[i]]=m/k+(i<m%k);
        for(int i=n-1;i>=0;i--){
            int u=q[i];
            if(dist[u]>=0){
                if(below[u]<dist[u]){
                    if(p[u]==0){
                        ok=false;
                    }else if(dist[p[u]]>=0){
                        ok=false;
                    }else{
                        dist[p[u]]=dist[u]-1;
                    }
                }
            }else{
                if(p[u]!=0){
                    below[p[u]]=max(below[p[u]],below[u]+1);
                }
            }
        }
        if(ok)l=m;
        else r=m-1;
    }
    cout << l << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}