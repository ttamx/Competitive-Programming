#include<bits/stdc++.h>

using namespace std;

using ll = long long;

template<class T>
using PQ = priority_queue<T,vector<T>,greater<T>>;

const int N=1e4+5;
const int L=1e5+5;

int n,m,k,s;
vector<tuple<int,int,int>> edges;
vector<pair<int,int>> adj[N];
PQ<pair<int,int>> pq[N];
int fa[N];
bool mark[N];
int a[L],b[L];
int st[N];
ll base;
ll dp[N];
PQ<tuple<int,int,int>> mpq;
ll ans=1e18;
ll vl[L],vr[L];

int fp(int u){
    return fa[u]=fa[u]==u?u:fp(fa[u]);
}

void norm(int u){
    u=fp(u);
    while(!pq[u].empty()&&fp(pq[u].top().second)==u){
        pq[u].pop();
    }
    if(!pq[u].empty()){
        auto [w,uu]=pq[u].top();
        mpq.emplace(w,u,uu);
    }
}

void merge(int u,int v){
    u=fp(u),v=fp(v);
    assert(u!=v);
    if(pq[u].size()<pq[v].size())swap(u,v);
    while(!pq[v].empty()){
        pq[u].emplace(pq[v].top());
        pq[v].pop();
    }
    fa[v]=u;
    mark[u]|=mark[v];
    norm(u);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    edges.resize(m);
    for(auto &[w,u,v]:edges){
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    cin >> k;
    for(int i=0;i<k;i++){
        cin >> a[i] >> b[i];
    }
    cin >> s;
    for(int i=0;i<s;i++){
        cin >> st[i];
        mark[st[i]]=true;
    }
    sort(edges.begin(),edges.end());
    for(int i=0;i<n;i++){
        fa[i]=i;
        for(auto [v,w]:adj[i]){
            pq[i].emplace(w,v);
        }
        norm(i);
    }
    for(auto [w,u,v]:edges){
        u=fp(u),v=fp(v);
        if(u==v||(mark[u]&&mark[v]))continue;
        merge(u,v);
        base+=w;
    }
    dp[s]=base;
    int idx=s;
    while(!mpq.empty()){
        auto [w,u,v]=mpq.top();
        mpq.pop();
        u=fp(u),v=fp(v);
        if(u==v)continue;
        merge(u,v);
        base+=w;
        dp[--idx]=base;
    }
    for(int i=1;i<=s;i++){
        cerr << dp[i] << " \n"[i==s];
    }
    assert(idx==1);
    int pos=min_element(b,b+k)-b;
    ll cur=dp[1]+1LL*(n-1)*b[pos];
    for(int i=0;i<k;i++){
        ll c=a[i];
        int l=1,r=s;
        auto f=[&](int x)->ll {
            return dp[x]+1LL*(n-x)*b[i]+1LL*x*c;
        };
        while(l<r){
            int m=(l+r)/2;
            if(f(m)>f(m+1)){
                l=m+1;
            }else{
                r=m;
            }
        }
        vr[i]=f(l);
    }
    for(int i=0;i<k;i++){
        ll c=a[(i+k-1)%k];
        int l=1,r=s;
        auto f=[&](int x)->ll {
            return dp[x]+1LL*(n-x)*b[i]+1LL*x*c;
        };
        while(l<r){
            int m=(l+r)/2;
            if(f(m)>f(m+1)){
                l=m+1;
            }else{
                r=m;
            }
        }
        vl[i]=f(l);
    }
    for(int i=0;i<k;i++){
        if(i!=pos){
            cur+=vr[i];
        }
    }
    ans=cur;
    for(int i=1;i<k;i++){
        int j=(pos+i)%k;
        cur+=vl[j]-vr[j];
        ans=min(ans,cur);
    }
    cout << ans;
}