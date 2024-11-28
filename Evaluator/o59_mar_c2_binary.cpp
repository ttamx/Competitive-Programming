#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> adj(n);
    for(int i=1;i<n;i++){
        int p;
        cin >> p;
        adj[p-1].emplace_back(i);
    }
    auto dfs=[&](auto &&self,int u,int p)->int{
        priority_queue<int,vector<int>,greater<int>> pq;
        for(auto v:adj[u]){
            pq.emplace(self(self,v,u));
        }
        if(pq.empty())return 0;
        if(pq.size()==1)return pq.top()+1;
        while(pq.size()>=2){
            int x=pq.top();pq.pop();
            int y=pq.top();pq.pop();
            pq.emplace(max(x,y)+1);
        }
        return pq.top();
    };
    cout << dfs(dfs,0,-1) << "\n";
}