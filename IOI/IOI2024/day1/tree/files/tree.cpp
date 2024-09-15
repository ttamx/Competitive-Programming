#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using pii = pair<int,int>;

const int N=2e5+5;

int n,m;
int p[N];
ll w[N],tot[N];
map<ll,ll> pq[N];
ll val[N];
vector<int> adj[N];
bool vis[N];
vector<ll> a,qs;
ll leaf;

int dfs(int u){
    vis[u]=true;
    if(w[u]==0){
        return 1;
    }
    int cnt=0;
    for(auto v:adj[u]){
        cnt+=dfs(v);
    }
    return max(cnt,1);
}

void init(vector<int> P,vector<int> W){
    n=P.size();
    for(int i=0;i<n;i++){
        p[i]=P[i];
        w[i]=W[i];
        if(i>0){
            adj[p[i]].emplace_back(i);
        }
    }
    for(int i=0;i<n;i++){
        if(!vis[i]){
            int cnt=dfs(i);
            if(w[i]>0){
                a.emplace_back(cnt);
            }
        }
    }
    for(int i=0;i<n;i++){
        if(adj[i].size()==0&&w[i]>0){
            leaf++;
        }
    }
    sort(a.begin(),a.end());
    qs=a;
    for(int i=1;i<qs.size();i++){
        qs[i]+=qs[i-1];
    }
}

ll query(int L,int R){
    ll ans=leaf*L;
    int idx=upper_bound(a.begin(),a.end(),R/L)-a.begin();
    if(idx<a.size()){
        ll val=qs.back();
        if(idx>0){
            val-=qs[idx-1];
        }
        val*=L;
        val-=1LL*(a.size()-idx)*R;
        ans+=val;
    }
    return ans;
}
