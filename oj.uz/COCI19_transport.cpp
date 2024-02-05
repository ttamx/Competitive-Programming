#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using pl = pair<ll,ll>;

const int N=1e5+5;
const int M=2e5+5;

struct fenwick{
    int t[M];
    void update(int i,int v){
        for(;i<M;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int n;
ll a[N];
vector<pl> adj[N];
int sz[N];
bool used[N];
ll ans;

struct Info{
    ll need,spare;
    Info():need(0),spare(0){}
    Info(ll _need,ll _spare):need(_need),spare(_spare){}
    friend Info operator+(Info lhs,Info rhs){
        ll used=min(lhs.spare,rhs.need);
        lhs.spare-=used;
        rhs.need-=used;
        return Info(lhs.need+rhs.need,lhs.spare+rhs.spare);
    }
}dp_st[N],dp_ed[N];

int get_sz(int u,int p=0){
    sz[u]=1;
    for(auto [v,w]:adj[u])if(v!=p&&!used[v])sz[u]+=get_sz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]&&sz[v]>cnt)return centroid(v,cnt,u);
    return u;
}

void dfs_st(int u,int p,vector<ll> &vec){
    if(dp_st[u].need==0)vec.emplace_back(dp_st[u].spare);
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]){
        dp_st[v]=Info(max(0LL,w-a[v]),max(0LL,a[v]-w))+dp_st[u];
        dfs_st(v,u,vec);
    }
}

void dfs_ed(int u,int p,vector<ll> &vec){
    vec.emplace_back(dp_ed[u].need);
    for(auto [v,w]:adj[u])if(v!=p&&!used[v]){
        dp_ed[v]=dp_ed[u]+Info(w,a[v]);
        dfs_ed(v,u,vec);
    }
}

void decom(int u){
    u=centroid(u,get_sz(u)/2);
    used[u]=true;
    vector<vector<ll>> st,ed;
    vector<ll> val{a[u]};
    for(auto [v,w]:adj[u])if(!used[v]){
        st.push_back({});
        ed.push_back({});
        dp_st[v]=Info(max(0LL,w-a[v]),max(0LL,a[v]-w)+a[u]);
        dp_ed[v]=Info(w,a[v]);
        dfs_st(v,u,st.back());
        dfs_ed(v,u,ed.back());
        for(auto x:st.back())val.emplace_back(x);
    }
    sort(val.begin(),val.end());
    auto get=[&](ll x){
        return lower_bound(val.begin(),val.end(),x)-val.begin()+1;
    };
    int cnt=0;
    for(auto &v:st)for(auto &x:v){
        x=get(x);
        f.update(x,1);
        cnt++;
    }
    ans+=cnt++;
    f.update(get(a[u]),1);
    int m=st.size();
    for(int i=0;i<m;i++){
        for(auto x:st[i])f.update(x,-1),cnt--;
        for(auto x:ed[i])ans+=cnt-f.query(get(x)-1);
        for(auto x:st[i])f.update(x,1),cnt++;
    }
    f.update(get(a[u]),-1);
    for(auto &v:st)for(auto &x:v)f.update(x,-1);
    for(auto [v,w]:adj[u])if(!used[v])decom(v);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<n;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    decom(1);
    cout << ans << "\n";
}