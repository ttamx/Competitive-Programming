#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> in(n),out(n);
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        in[v].emplace_back(u);
        out[u].emplace_back(v);
    }
    vector<vector<int>> cnt(n,vector<int>(n));
    for(int u=0;u<n;u++){
        for(auto x:in[u]){
            for(auto y:out[u]){
                cnt[x][y]++;
            }
        }
    }
    long long ans=0;
    for(int u=0;u<n;u++){
        for(int v=0;v<n;v++){
            if(u!=v&&cnt[u][v]>1){
                ans+=1LL*cnt[u][v]*(cnt[u][v]-1);
            }
        }
    }
    cout << ans/2 << "\n";
}