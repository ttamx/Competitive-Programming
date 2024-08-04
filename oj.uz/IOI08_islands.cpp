#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;

int n;
pair<int,int> nxt[N];
int deg[N];
queue<int> q;
ll dp[N],dp2[N],dia[N];
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        auto &[v,w]=nxt[i];
        cin >> v >> w;
        deg[v]++;
    }
    for(int i=1;i<=n;i++)if(!deg[i])q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        auto [v,w]=nxt[u];
        dp2[v]=max(dp2[v],dp[u]+w);
        if(dp[v]<dp2[v])swap(dp[v],dp2[v]);
        dia[v]=max({dia[v],dia[u],dp[v]+dp2[v]});
        if(--deg[v]==0)q.emplace(v);
    }
    for(int i=1;i<=n;i++)if(deg[i]){
        vector<pair<int,ll>> comp;
        ll len=0;
        for(int u=i;deg[u];){
            comp.emplace_back(u,len);
            deg[u]=0;
            auto [v,w]=nxt[u];
            len+=w;
            u=v;
        }
        ll res=0;
        deque<pair<ll,int>> dq;
        for(auto [u,w]:comp){
            res=max(res,dia[u]);
            ll val=dp[u]-w;
            while(!dq.empty()&&dq.back().first<val)dq.pop_back();
            dq.emplace_back(val,u);
        }
        for(auto [u,w]:comp){
            if(dq.front().second==u)dq.pop_front();
            res=max(res,w+len+dp[u]+dq.front().first);
            ll val=dp[u]-w-len;
            while(!dq.empty()&&dq.back().first<val)dq.pop_back();
            dq.emplace_back(val,u);
        }
        ans+=res;
    }
    cout << ans;
}