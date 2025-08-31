#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m;
    cin >> m;
    vector<pair<int,int>> e(m);
    vector<int> a;
    for(auto &[l,r]:e){
        cin >> l >> r;
        r++;
        a.emplace_back(l);
        a.emplace_back(r);
    }
    sort(a.begin(),a.end());
    a.erase(unique(a.begin(),a.end()),a.end());
    int n=a.size();
    vector<vector<pair<int,int>>> adj(n);
    for(int i=0;i<m;i++){
        auto &[l,r]=e[i];
        l=lower_bound(a.begin(),a.end(),l)-a.begin();
        r=lower_bound(a.begin(),a.end(),r)-a.begin();
        adj[l].emplace_back(r,i);
        adj[r].emplace_back(l,i);
    }
    vector<int> b;
    for(int i=0;i<n;i++){
        if(adj[i].size()%2==1){
            b.emplace_back(i);
        }
    }
    int buf=m;
    for(int i=0;i<b.size();i+=2){
        int l=b[i],r=b[i+1];
        adj[l].emplace_back(r,buf);
        adj[r].emplace_back(l,buf);
        buf++;
    }
    vector<int> ptr(n),ans(m);
    vector<bool> used(buf);
    function<void(int)> dfs=[&](int u){
        for(int &i=ptr[u];i<adj[u].size();i++){
            auto [v,j]=adj[u][i];
            if(used[j])continue;
            used[j]=true;
            dfs(v);
            if(j<m){
                ans[j]=(u<v);
            }
        }
    };
    for(int i=0;i<n;i++){
        dfs(i);
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}