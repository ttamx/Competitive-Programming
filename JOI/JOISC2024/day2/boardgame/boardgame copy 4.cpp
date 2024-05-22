#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=100005;
const int INF=INT_MAX/2;
const ll LINF=LLONG_MAX/2;;
const int T=1e5;

int n,m,k;
vector<int> adj[N];
string s;
bool stop[N],good[N];
bool have_stop,have_good;
int a[N];
int ds[N],dg[N];
ll step[N];
ll dp[N],ans[N];

void build_stop(){
    queue<int> q;
    for(int u=1;u<=n;u++)if(stop[u]){
        for(auto v:adj[u])if(!ds[v]){
            ds[v]=1;
            q.emplace(v);
        }
    }
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto v:adj[u])if(!ds[v]){
            ds[v]=ds[u]+1;
            q.emplace(v);
        }
    }
}

void build_good(){
    using P = pair<int,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=1;i<=n;i++)dg[i]=INF;
    for(int u=1;u<=n;u++)if(good[u]){
        for(auto v:adj[u])if(dg[v]>0){
            dg[v]=1;
            pq.emplace(1,v);
        }
    }
    while(!pq.empty()){
        auto [d,u]=pq.top();
        pq.pop();
        int nd=d+1;
        if(stop[u])nd--;
        for(auto v:adj[u])if(nd<dg[v]){
            dg[v]=nd;
            pq.emplace(nd,v);
        }
    }
}

void build_step(){
    for(int i=2;i<=k;i++){
        int u=a[i];
        int pre=0;
        for(int j=1;j<=T;j++){
            int res=ds[u]+(j-1)*2;
            if(have_good)res=min(res,dg[u]+j-1);
            step[j]+=res-pre;
            pre=res;
        }
    }
}

void build_answer(){
    using P=tuple<ll,int,int>;
    priority_queue<P,vector<P>,greater<P>> pq;
    for(int i=1;i<=n;i++)dp[i]=LINF;
    for(int i=1;i<=n;i++)ans[i]=LINF;
    dp[a[1]]=0;
    ans[a[1]]=0;
    pq.emplace(0,a[1],0);
    while(!pq.empty()){
        auto [d,u,t]=pq.top();
        pq.pop();
        for(auto v:adj[u]){
            ll nd=d+1;
            int nt=t;
            ans[v]=min(ans[v],nd);
            if(stop[v]){
                nt=min(t+1,T);
                nd+=step[nt];
            }
            if(nd<dp[v]){
                dp[v]=nd;
                pq.emplace(nd,v,nt);
            }
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=0;i<m;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    cin >> s;
    for(int i=1;i<=n;i++)stop[i]=(s[i-1]=='1');
    for(int i=1;i<=k;i++)cin >> a[i];
    for(int u=1;u<=n;u++)if(stop[u]){
        have_stop=true;
        for(auto v:adj[u])if(stop[v]){
            have_good=true;
            good[u]=good[v]=true;
        }
    }
    if(have_stop)build_stop();
    if(have_good)build_good();
    if(have_stop)build_step();
    build_answer();
    for(int i=1;i<=n;i++)cout << ans[i] << "\n";
}