#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=150005;
const ll INF=2e18;

int n;
vector<int> adj[N];
int a[N];
int sz[N];
bool used[N];
ll ans=0;

ll floor(ll a,ll b){
    return a/b-((a^b)<0&&a%b);
}

bool querymode=false;

struct Line{
    ll m,c;
    mutable ll p;
    bool operator<(const Line &o)const{
        return querymode?p<o.p:m<o.m;
    }
};

struct LineContainer:multiset<Line>{
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=INF,false;
        if(x->m==y->m)x->p=x->c>=y->c?INF:-INF;
        else x->p=floor(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void update(ll m,ll c){
        auto x=insert(Line{m,c,0}),y=next(x);
        while(isect(x,y))y=erase(y);
        while((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
    }
    ll query(ll x){
        querymode=true;
        auto it=lower_bound(Line{0,0,x});
        querymode=false;
        return it==end()?-INF:it->m*x+it->c;
    }
}ds;

int dfs_sz(int u,int p){
    sz[u]=1;
    for(auto v:adj[u]){
        if(v!=p&&!used[v]){
            sz[u]+=dfs_sz(v,u);
        }
    }
    return sz[u];
}

int centroid(int u,int p,int s){
    for(auto v:adj[u]){
        if(v!=p&&!used[v]&&sz[v]*2>s){
            return centroid(v,u,s);
        }
    }
    return u;
}

void dfs_update(int u,int p,int cnt,ll val,ll sum){
    cnt++;
    val+=a[u];
    sum+=1LL*a[u]*cnt;
    ans=max(ans,sum);
    ds.update(val,sum);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs_update(v,u,cnt,val,sum);
    }
}

void dfs_query(int u,int p,int cnt,ll val,ll sum){
    cnt++;
    val+=a[u];
    sum+=val;
    ans=max(ans,ds.query(cnt)+sum);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs_query(v,u,cnt,val,sum);
    }
}

void dfs_ans(int u,int p,int cnt,ll val,ll sum){
    cnt++;
    val+=a[u];
    sum+=val;
    ans=max(ans,sum);
    for(auto v:adj[u]){
        if(v==p||used[v])continue;
        dfs_ans(v,u,cnt,val,sum);
    }
}

void decom(int u){
    u=centroid(u,0,dfs_sz(u,0));
    used[u]=true;
    dfs_ans(u,0,0,0,0);
    for(int t=0;t<2;t++){
        ds.update(a[u],a[u]);
        for(auto v:adj[u]){
            if(used[v])continue;
            dfs_query(v,u,0,0,0);
            dfs_update(v,u,1,a[u],a[u]);
        }
        ds.clear();
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto v:adj[u]){
        if(!used[v]){
            decom(v);
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v;
        cin >> u >> v;
        adj[u].emplace_back(v);
        adj[v].emplace_back(u);
    }
    for(int i=1;i<=n;i++){
        cin >> a[i];
        ans=max(ans,(ll)a[i]);
    }
    decom(1);
    cout << ans << "\n";
}