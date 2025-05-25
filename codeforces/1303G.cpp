#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=150005;
const ll INF=1e18;

struct Info{
    ll ans,sum,cnt;
    friend Info operator+(const Info &l,const Info &r){
        return Info{l.ans+r.ans+l.sum*r.cnt,l.sum+r.sum,l.cnt+r.cnt};
    }
};

int n;
ll a[N];
vector<int> adj[N];
Info b[N];
int sz[N];
bool used[N];
ll ans;
vector<pair<Info,Info>> cur;

struct Line{
    ll m,c;
    mutable ll p;
    Line(ll _m,ll _c):m(_m),c(_c),p(0){}
    bool operator<(const Line &o)const{return m<o.m;}
    bool operator<(const ll &o)const{return p<o;}
};

struct LineContainer:multiset<Line,less<>>{
    ll fdiv(ll a,ll b){return a/b-((a^b)<0&&a%b);}
    bool isect(iterator x,iterator y){
        if(y==end())return x->p=INF,false;
        if(x->m==y->m)x->p=x->c>=y->c?INF:-INF;
        else x->p=fdiv(x->c-y->c,y->m-x->m);
        return x->p>=y->p;
    }
    void update(ll m,ll c){
        auto x=insert(Line(m,c)),y=next(x);
        while(isect(x,y))y=erase(y);
        if((y=x)!=begin()&&isect(--x,y))isect(x,erase(y));
        while((y=x)!=begin()&&(--x)->p>=y->p)isect(x,erase(y));
    }
    ll query(ll x){
        if(empty())return -INF;
        auto it=lower_bound(x);
        return it->m*x+it->c;
    }
}cht1,cht2;

int dfs_sz(int u,int p=0){
    sz[u]=1;
    for(auto v:adj[u])if(v!=p&&!used[v])sz[u]+=dfs_sz(v,u);
    return sz[u];
}

int centroid(int u,int cnt,int p=0){
    for(auto v:adj[u])if(v!=p&&!used[v]&&sz[v]*2>cnt)return centroid(v,cnt,u);
    return u;
}

void dfs(int u,Info s1,Info s2,int p=0){
    s1=s1+b[u];
    s2=b[u]+s2;
    cur.emplace_back(s1,s2);
    for(auto v:adj[u])if(v!=p&&!used[v])dfs(v,s1,s2,u);
}

void decom(int u){
    u=centroid(u,dfs_sz(u));
    used[u]=true;
    cht1.update(a[u],a[u]);
    cht2.update(1,a[u]);
    ans=max(ans,a[u]);
    for(auto v:adj[u])if(!used[v]){
        dfs(v,Info{0,0,0},Info{0,0,0});
        for(auto [s1,s2]:cur){
            ans=max(ans,cht1.query(s1.cnt)+s1.ans);
            ans=max(ans,cht2.query(s2.sum)+s2.ans);
        }
        for(auto [s1,s2]:cur){
            s1=b[u]+s1,s2=s2+b[u];
            cht1.update(s2.sum,s2.ans);
            cht2.update(s1.cnt,s1.ans);
        }
        cur.clear();
    }
    cht1.clear();
    cht2.clear();
    for(auto v:adj[u])if(!used[v])decom(v);
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
        b[i]=Info{a[i],a[i],1};
    }
    decom(1);
    cout << ans;
}