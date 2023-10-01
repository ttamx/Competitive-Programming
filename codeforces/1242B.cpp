#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,m;
map<int,bool> mp[N];
set<int> s;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)s.emplace(i);
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        mp[u][v]=mp[v][u]=true;
    }
    for(int i=1;i<=n;i++){
        auto it=s.find(i);
        if(it==s.end())continue;
        ans++;
        s.erase(it);
        queue<int> q;
        q.emplace(i);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(it=s.begin();it!=s.end();){
                if(mp[u][*it]){
                    it++;
                    continue;
                }
                q.emplace(*it);
                it=s.erase(it);
            }
        }
    }
    cout << ans-1;
}