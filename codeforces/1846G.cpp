#include<bits/stdc++.h>

using namespace std;

const int inf=2e9;

int getval(){
    string s;
    cin >> s;
    int res=0;
    for(auto x:s)res=res<<1|(x-'0');
    return res;
}

void runcase(){
    int n,m,s;
    cin >> n >> m;
    s=getval();
    vector<tuple<int,int,int>> a(m);
    for(auto &[u,v,w]:a){
        cin >> w;
        u=getval();
        v=getval();
    }
    vector<int> dp(1<<n,inf);
    vector<bool> vis(1<<n);
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    dp[s]=0;
    pq.emplace(0,s);
    while(!pq.empty()){
        auto [d,i]=pq.top();
        pq.pop();
        if(vis[i])continue;
        vis[i]=true;
        for(auto [u,v,w]:a){
            int j=i&~u|v;
            if(d+w<dp[j]){
                dp[j]=d+w;
                pq.emplace(d+w,j);
            }
        }
    }
    cout << (dp[0]==inf?-1:dp[0]) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}