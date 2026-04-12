#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<int,int,int>;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> a(n,vector<int>(m));
    for(auto &v:a)for(auto &x:v)cin >> x;
    vector<vector<int>> dist(n,vector<int>(m,INF));
    priority_queue<T,vector<T>,greater<T>> pq;
    auto go=[&](int i,int j,int d){
        if(i<0||i>=n||j<0||j>=m||d>=dist[i][j])return;
        dist[i][j]=d;
        pq.emplace(d,i,j);
    };
    for(int i=0;i<k;i++){
        int x,y;
        cin >> x >> y;
        x--,y--;
        go(x,y,i);
    }
    vector<vector<int>> c;
    while(!pq.empty()){
        auto [d,i,j]=pq.top();
        pq.pop();
        if(d>dist[i][j])continue;
        if(d>=c.size())c.emplace_back(vector<int>());
        c.back().emplace_back(a[i][j]);
        go(i-1,j,d+1);
        go(i,j-1,d+1);
        go(i,j+1,d+1);
        go(i+1,j,d+1);
    }
    reverse(c.begin(),c.end());
    priority_queue<int> pq2;
    ll ans=0;
    for(auto &v:c){
        for(auto x:v)pq2.emplace(x);
        if(!pq2.empty()){
            ans+=pq2.top();
            pq2.pop();
        }
    }
    cout << ans << "\n";
}