#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m;
vector<pair<int,int>> adj[N];
pair<int,int> pre[N];
int dp[N],deg[N];
ll sum[N];
queue<int> q;
map<pair<int,int>,int> mp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<m;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[v].emplace_back(u,w);
        deg[u]++;
    }
    for(int i=1;i<=n;i++)if(!deg[i])q.emplace(i);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [v,w]:adj[u]){
            if(--deg[v]==0)q.emplace(v);
            if(dp[u]+1>dp[v]){
                dp[v]=dp[u]+1;
                sum[v]=sum[u]+w;
                pre[v]={u,w};
            }else if(dp[u]+1==dp[v]){
                stack<pair<int,int>> s;
                int res=-1;
                for(int x=pre[v].second,y=w,i=pre[v].first,j=u;i;){
                    if(x!=y){
                        if(x>y)res=1;
                        break;
                    }
                    if(mp[{i,j}]){
                        res=mp[{i,j}];
                        break;
                    }
                    tie(i,x)=pre[i];
                    tie(j,y)=pre[j];
                    s.emplace(i,j);
                }
                if(res==1){
                    sum[v]=sum[u]+w;
                    pre[v]={u,w};
                }
                while(!s.empty()){
                    auto [i,j]=s.top();
                    s.pop();
                    mp[{i,j}]=res;
                    mp[{j,i}]=-res;
                }
            }
        }
    }
    for(int i=1;i<=n;i++)cout << dp[i] << " " << sum[i] << "\n";
}