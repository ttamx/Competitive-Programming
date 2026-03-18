#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

using ll = long long;

void runcase(){
    int n,x,y;
    cin >> n >> x >> y;
    x--,y--;
    vector<vector<int>> adj(n);
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        u--,v--;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    vector<bool> mark(n);
    function<pair<int,int>(int,int)> dfs=[&](int u,int p){
        int mx=0,mx2=0,dia=0;
        for(auto v:adj[u]){
            if(v==p||mark[v])continue;
            auto [v_mx,v_dia]=dfs(v,u);
            v_mx++;
            dia=max(dia,v_dia);
            mx2=max(mx2,v_mx);
            if(mx2>mx)swap(mx,mx2);
        }
        dia=max(dia,mx+mx2);
        return make_pair(mx,dia);
    };
    int ans=dfs(0,-1).second;
    vector<int> a;
    {
        queue<int> q;
        vector<int> par(n,-1);
        q.emplace(x);
        while(!q.empty()){
            int u=q.front();
            q.pop();
            for(auto v:adj[u]){
                if(v!=par[u]){
                    par[v]=u;
                    q.emplace(v);
                }
            }
        }
        for(int u=y;u!=-1;u=par[u]){
            a.emplace_back(u);
        }
    }
    int m=a.size();
    int mx_dia=0;
    vector<pair<int,int>> dp(m);
    for(int i=0;i<m;i++){
        int u=a[i];
        dp[i]=dfs(u,(i+1<m?a[i+1]:-1));
        mx_dia=max(mx_dia,dp[i].second);
        mark[u]=true;
    }
    ans=max(ans,mx_dia+(m-1));
    vector<int> pre_mx(m),pre_mx2(m),pre_dia(m),suf_mx(m),suf_mx2(m),suf_dia(m);
    {
        int pre=0,pre2=0,suf=0;
        int cur_dia=0;
        for(int i=0;i<m;i++){
            auto [mx,dia]=dp[i];
            pre=max(pre,mx+i);
            pre2=max(pre2,mx);
            cur_dia=max(cur_dia,dia);
            cur_dia=max(cur_dia,suf+mx);
            suf=max(suf,mx)+1;
            pre_mx[i]=pre;
            pre_mx2[i]=pre2;
            pre_dia[i]=dia;
        }
    }
    {
        int pre=0,pre2=0,suf=0;
        int cur_dia=0;
        for(int i=m-1;i>=0;i--){
            auto [mx,dia]=dp[i];
            pre=max(pre,mx+(m-i-1));
            pre2=max(pre2,mx);
            cur_dia=max(cur_dia,dia);
            cur_dia=max(cur_dia,suf+mx);
            suf=max(suf,mx)+1;
            suf_mx[i]=pre;
            suf_mx2[i]=pre2;
            suf_dia[i]=dia;
        }
    }
    for(int i=0;i+1<m;i++){
        ans=max(ans,pre_mx[i]+suf_mx[i+1]+2);
        ans=max(ans,pre_mx2[i]+suf_mx2[i+1]+m-1);
        ans=max(ans,pre_dia[i]+2);
        ans=max(ans,suf_dia[i+1]+2);
    }
    cout << (n-1)*2-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}