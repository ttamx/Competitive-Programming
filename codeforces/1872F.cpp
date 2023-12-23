#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),c(n),deg(n);
    for(auto &x:a){
        cin >> x;
        x--;
        deg[x]++;
    }
    for(auto &x:c)cin >> x;
    vector<bool> vis(n);
    vector<int> ans;
    for(int i=0;i<n;i++)if(deg[i]==0)ans.emplace_back(i),vis[i]=true;
    for(int i=0;i<ans.size();i++){
        int u=ans[i];
        vis[u]=true;
        int v=a[u];
        if(--deg[v]==0)ans.emplace_back(v);
    }
    for(int i=0;i<n;i++){
        if(vis[i])continue;
        int u=i;
        vis[u]=true;
        pair<int,int> best(c[u],u);
        while(a[u]!=i){
            u=a[u];
            vis[u]=true;
            best=min(best,{c[u],u});
        }
        int st=best.second;
        u=st;
        while(a[u]!=st){
            u=a[u];
            ans.emplace_back(u);
        }
        ans.emplace_back(st);
    }
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}