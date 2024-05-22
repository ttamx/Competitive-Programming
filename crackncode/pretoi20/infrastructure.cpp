#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=LLONG_MAX/2;

int n,m,q,s;
vector<int> adj[N];
ll a[N],d[N],mx[N],pre[N],sum[N],cnt[N],cum[N];
priority_queue<ll> pq;
vector<ll> val[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> s >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    queue<int> qu;
    qu.emplace(s);
    d[s]=1;
    while(!qu.empty()){
        int u=qu.front();
        qu.pop();
        for(auto v:adj[u])if(!d[v]){
            d[v]=d[u]+1;
            qu.emplace(v);
        }
    }
    for(int i=1;i<=n;i++){
        val[d[i]].emplace_back(a[i]);
        cnt[d[i]+1]++;
    }
    ll ans=0;
    for(int i=n;i>=2;i--){
        for(auto x:val[i])pq.emplace(x);
        if(!pq.empty()){
            mx[i]=pq.top();
            pq.pop();
        }
        ans+=mx[i];
    }
    for(int i=2;i<=n+1;i++)pre[i]=mx[i];
    for(int i=3;i<=n+1;i++)pre[i]=min(pre[i],pre[i-1]);
    for(int i=2;i<=n+1;i++){
        cum[i]=cum[i-1]+cnt[i];
        sum[i]=sum[i-1]-pre[i]*cnt[i];
    }
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int x;
            ll y;
            cin >> x >> y;
            cout << ans+max(0LL,y-pre[d[x]+1]) << "\n";
        }else{
            ll y;
            cin >> y;
            int l=1,r=n+2;
            while(l<r){
                int m=(l+r+1)/2;
                if(pre[m]>y)l=m;
                else r=m-1;
            }
            cout << ans*n+sum[n+1]-sum[l]+y*(cum[n+1]-cum[l]) << "\n";
        }
    }
}