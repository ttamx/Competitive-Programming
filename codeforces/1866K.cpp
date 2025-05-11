#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;
const ll INF=1e18;

int n,q;
vector<pair<int,int>> adj[N],qr[N];
ll ans[N],ans2[N];

struct Info{
    ll ans,dep;
    friend Info operator+(const Info &l,const Info &r){
        return {max({l.ans,r.ans,l.dep+r.dep}),max(l.dep,r.dep)};
    }
}dp[N],up[N];

Info add(Info c,int v){
    c.dep+=v;
    c.ans=max(c.ans,c.dep);
    return c;
}

struct Line{
    ll m,c;
    mutable ll p;
    int id;
    ll eval(ll x){return m*x+c;}
    bool operator<(const Line &o)const{return m<o.m;}
    bool operator<(const ll &x)const{return p<x;}
};

struct CHT:multiset<Line,less<>>{
    ll div(ll a,ll b){return a/b-((a^b)<0&&a%b);}
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=INF,false;
        if(x->m==y->m)x->p=x->c>=y->c?INF:-INF;
        else x->p=div(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void addline(Line v){
        auto x=insert(v),y=next(x);
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    pair<ll,int> query(ll x){
        if(empty())return {0,-1};
        auto it=lower_bound(x);
        return {it->m*x+it->c,it->id};
    }
};

void solve(vector<Line> a,int u){
    if(a.empty())return;
    int c=a.size();
    CHT cht;
    for(int i=0;i<a.size();i++){
        a[i].id=i;
        cht.addline(a[i]);
    }
    vector<vector<pair<int,int>>> opt(c);
    for(auto [i,k]:qr[u]){
        auto [v,j]=cht.query(k);
        assert(j!=-1);
        opt[j].emplace_back(i,k);
        ans[i]=v;
    }
    cht.clear();
    for(int i=0;i<c;i++){
        for(auto [j,k]:opt[i])ans2[j]=max(ans2[j],cht.query(k).first);
        cht.addline(a[i]);
    }
    cht.clear();
    for(int i=c-1;i>=0;i--){
        for(auto [j,k]:opt[i])ans2[j]=max(ans2[j],cht.query(k).first);
        cht.addline(a[i]);
    }
    for(auto [i,k]:qr[u])ans[i]+=ans2[i];
}

void dfs(int u,int p){
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        dfs(v,u);
        dp[u]=dp[u]+add(dp[v],w);
    }
}

void reroot(int u,int p,int pw){
    ll diam=0;
    vector<Line> a;
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        a.emplace_back(Line{w,dp[v].dep,0});
        diam=max(diam,dp[v].ans);
    }
    if(p){
        a.emplace_back(Line{pw,up[u].dep,0});
        diam=max(diam,up[u].ans);
    }
    solve(a,u);
    for(auto [i,k]:qr[u])ans[i]=max(ans[i],diam);
    for(int t=0;t<2;t++){
        Info sum{0,0};
        for(auto [v,w]:adj[u]){
            if(v==p)continue;
            up[v]=up[v]+sum;
            sum=sum+add(dp[v],w);
        }
        reverse(adj[u].begin(),adj[u].end());
    }
    for(auto [v,w]:adj[u]){
        if(v==p)continue;
        up[v]=up[v]+add(up[u],pw);
        reroot(v,u,w);
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n-1;i++){
        int u,v,w;
        cin >> u >> v >> w;
        adj[u].emplace_back(v,w);
        adj[v].emplace_back(u,w);
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int u,k;
        cin >> u >> k;
        qr[u].emplace_back(i,k);
    }
    dfs(1,0);
    reroot(1,0,0);
    for(int i=1;i<=q;i++)cout << ans[i] << "\n";
}