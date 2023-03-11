#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=5e4+5;
const int K=1<<17;

int n,m,k;
int pos[N];
bool vis[N];
ll a[N],qs[N],dp[N],mn[N];
vector<pair<int,ll>> adj[N];
vector<ll> in;

struct fenwick{
    vector<ll> f;
    void init(){
        f=vector<ll>(N,1e18);
    }
    void add(int i,ll v){
        while(i<n)f[i]=min(f[i],v),i+=i&-i;
    }
    ll read(int i){
        ll ret=1e18;
        while(i)ret=min(ret,f[i]),i-=i&-i;
        return ret;
    }
}f1,f2;

long long minimum_energy(int N, int M, int K,vector<int> A,vector<int> L,vector<int> R,vector<int> C){
    n=N,m=M,k=K;
    for(int i=1;i<=n;i++){
        a[i]=A[i-1];
        qs[i]=qs[i-1]+a[i];
        dp[i]=1e18;
        adj[i].push_back({i-1,a[i]});
        adj[i-1].push_back({i,a[i]});
        in.push_back(a[i]);
    }
    sort(in.begin(),in.end());
    in.erase(unique(in.begin(),in.end()),in.end());
    for(int i=1;i<=n;i++)pos[i]=lower_bound(in.begin(),in.end(),a[i])-in.begin()+1;
    for(int i=0;i<m;i++){
        adj[L[i]].push_back({R[i]+1,C[i]});
        adj[R[i]+1].push_back({L[i],C[i]});
    }
    priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>> pq;
    auto dijk=[&](){
        for(int i=0;i<=n;i++)vis[i]=false;
        while(!pq.empty()){
            auto [d,u]=pq.top();
            pq.pop();
            if(vis[u])continue;
            vis[u]=true;
            for(auto [v,w]:adj[u]){
                if(d+w<dp[v]){
                    dp[v]=d+w;
                    pq.push({d+w,v});
                }
            }
        }
    };
    pq.push({0,0});
    dijk();
    for(int l=1;l<=k;l++){
        f1.init();
        f2.init();
        for(int i=n;i>=0;i--){
            ll q1=1e18,q2=1e18;
            q1=f1.read(pos[i+1]+1)+a[i+1]*a[i+1];
            q2=f2.read(n-pos[i+1]+1)-a[i+1]*a[i+1];
            f1.add(pos[i]+1,dp[i]-a[i]*a[i]);
            f2.add(n-pos[i]+1,dp[i]+a[i]*a[i]);
            mn[i]=min(q1,q2);
        }
        f1.init();
        f2.init();
        for(int i=0;i<=n;i++){
            ll q1=1e18,q2=1e18;
            q1=f1.read(pos[i]+1)+a[i]*a[i];
            q2=f2.read(n-pos[i]+1)-a[i]*a[i];
            f1.add(pos[i+1]+1,dp[i]-a[i+1]*a[i+1]);
            f2.add(n-pos[i+1]+1,dp[i]+a[i+1]*a[i+1]);
            mn[i]=min({mn[i],q1,q2});
        }
        for(int i=1;i<=n;i++){
            if(mn[i]<dp[i]){
                dp[i]=mn[i];
                pq.push({dp[i],i});
            }
        }
        dijk();
    }
    return dp[n];
}
