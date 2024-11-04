#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(n,vector<int>(m)),b(n,vector<int>(m));
    for(auto &v:a)for(auto &x:v)cin >> x;
    for(auto &v:b)for(auto &x:v)cin >> x;
    queue<int> q;
    vector<int> cnt(n);
    vector<ll> val(m);
    vector<priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>> pq(m);
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(a[i][j])pq[j].emplace(a[i][j],i);
            else cnt[i]++;
        }
        if(cnt[i]==m)q.emplace(i);
    }
    int ans=0;
    while(!q.empty()){
        int u=q.front();
        q.pop();
        ans++;
        for(int i=0;i<m;i++){
            val[i]+=b[u][i];
            while(!pq[i].empty()&&pq[i].top().first<=val[i]){
                int v=pq[i].top().second;
                pq[i].pop();
                cnt[v]++;
                if(cnt[v]==m)q.emplace(v);
            }
        }
    }
    cout << ans << "\n";
}