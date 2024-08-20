#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;

vector<int> factor[N];

int a[N];
vector<pair<int,int>> adj[N];
bool ok[N];
ll mx[N];
int sz[N];
bool used[N];
ll ans;

int dfs_sz(int u,int p=-1){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=-1){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&v>cnt/2)return centroid(v,cnt,u);
    return u;
}

vector<pair<int,ll>> comp;

void dfs(int u,ll d,int p){
    comp.emplace_back(u,d);
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])dfs(v,d+w,u);
}

vector<int> pos;

void update(int u,ll d){
    pos.emplace_back(a[u]);
    for(auto i:factor[a[u]]){
        ok[i]=true;
        mx[i]=max(mx[i],d);
    }
}

void query(int u,ll d){
    for(auto i:factor[a[u]]){
        ans=max(ans,(mx[i]+d)*i);
    }
}

void clear(){
    for(auto x:pos){
        for(auto i:factor[x]){
            ok[i]=false;
            mx[i]=0;
        }
    }
    pos.clear();
}

void decom(int u){
    u=centroid(u,dfs_sz(u));
    used[u]=true;
    update(u,0);
    for(auto [v,w]:adj[u])if(!used[v]){
        dfs(v,w,u);
        for(auto [i,d]:comp)query(i,d);
        for(auto [i,d]:comp)update(i,d);
        comp.clear();
    }
    clear();
    for(auto [v,w]:adj[u])if(!used[v])decom(v);
}

void runcase(int n){
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    ans=0;
    decom(1);
    cout << ans << "\n";
    for(int i=1;i<=n;i++){
        adj[i].clear();
        used[i]=false;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<N;i++){
        for(int j=i;j<N;j+=i){
            factor[j].emplace_back(i);
        }
    }
    while(true){
        int n;
        cin >> n;
        if(n==0)break;
        runcase(n);
    }
}