#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n;
int a[N];
int cyc[N],deg[N];
int mn[N],mn2[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        deg[a[i]]++;
    }
    for(int i=1;i<=n;i++){
        if(!deg[i]){
            q.emplace_back(i);
        }
    }
    for(int i=0;i<q.size();i++){
        int u=q[i];
        if(--deg[a[u]]==0){
            q.emplace_back(a[u]);
        }
    }
    for(int i=1;i<=n;i++){
        if(!deg[i])continue;
        vector<int> path;
        for(int u=i;!cyc[u];u=a[u]){
            cyc[u]=i;
            path.emplace_back(u);
        }
        for(int j=path.size()-1;j>0;j--){
            ans.emplace_back(1,path[j-1],path[j]);
        }
    }
    reverse(q.begin(),q.end());
    for(auto u:q){
        ans.emplace_back(2,a[u],u);
    }
    cout << ans.size() << "\n";
    for(auto [o,x,y]:ans){
        cout << o << " " << x << " " << y << "\n";
    }
}