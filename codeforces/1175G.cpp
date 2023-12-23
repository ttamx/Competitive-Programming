#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=20005;
const int K=105;
const int S=1<<16;
const ll inf=1e18;

int n,k;
ll a[N];
ll dp[N][K];
int l[N],r[N];

struct CHT{
    struct line{
        ll m,c;
        line(ll m,ll c):m(m),c(c){}
        ll get(ll x){
            return m*x+c;
        }
    };
    deque<line> dq;
    void clear(){
        dq.clear();
    }
    bool bad(line x,line y,line z){
        return 1.l*(z.c-x.c)*(x.m-y.m)<=1.l*(y.c-x.c)*(x.m-z.m);
    }
    void insert(ll m,ll c){
        line l(m,c);
        while(dq.size()>1&&bad(dq.end()[-2],dq.back(),l))dq.pop_back();
        dq.emplace_back(l);
    }
    ll query(ll x){
        if(dq.empty())return inf;
        while(dq.size()>1&&dq[0].get(x)>dq[1].get(x))dq.pop_front();
        return dq[0].get(x);
    }
};

struct segtree{
    CHT t[S];
    void build(int l,int r,int i){
        t[i].clear();
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,ll m,ll c){
        if(x<l||r<x)return;
        t[i].insert(m,c);
        if(l==r)return;
        int mid=(l+r)/2;
        update(l,mid,i*2,x,m,c);
        update(mid+1,r,i*2+1,x,m,c);
    }
    void update(int x,ll m,ll c){
        update(1,n,1,x,m,c);
    }
    void update(int l,int r,int i,int x,int y,ll m,ll c){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return t[i].insert(m,c);
        int mid=(l+r)/2;
        update(l,mid,i*2,x,y,m,c);
        update(mid+1,r,i*2+1,x,y,m,c);
    }
    void update(int x,int y,ll m,ll c){
        update(1,n,1,x,y,m,c);
    }
    ll query(int l,int r,int i,int x,ll v){
        if(x<l||r<x)return inf;
        ll res=t[i].query(v);
        if(l==r)return res;
        int m=(l+r)/2;
        return min({res,query(l,m,i*2,x,v),query(m+1,r,i*2+1,x,v)});
    }
    ll query(int x,ll v){
        return query(1,n,1,x,v);
    }
    ll query(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return inf;
        if(x<=l&&r<=y)return t[i].query(v);
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y,v),query(m+1,r,i*2+1,x,y,v));
    }
    ll query(int x,int y,ll v){
        return query(1,n,1,x,y,v);
    }
}s1,s2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++)cin >> a[i];
    ll mx=-inf;
    stack<int> s;
    a[0]=inf;
    s.emplace(0);
    for(int i=1;i<=n;i++){
        mx=max(mx,a[i]);
        dp[i][1]=mx*i;
        while(a[s.top()]<=a[i]){
            r[s.top()]=i-1;
            s.pop();
        }
        l[i]=s.top()+1;
        r[i]=n;
        s.emplace(i);
    }
    vector<int> pos(n);
    iota(pos.begin(),pos.end(),1);
    sort(pos.begin(),pos.end(),[&](int x,int y){
        return a[x]<a[y];
    });
    for(int j=2;j<=k;j++){
        s1.build();
        s2.build();
        for(int i=0;i<n;i++)s1.update(i+1,-i,dp[i][j-1]);
        vector<pair<ll,int>> res;
        for(auto i:pos)res.emplace_back(s1.query(l[i],i,a[i]),i);
        reverse(res.begin(),res.end());
        for(auto [c,i]:res)s2.update(i,r[i],a[i],c);
        for(int i=1;i<=n;i++)dp[i][j]=s2.query(i,i);
    }
    cout << dp[n][k] << "\n";
}