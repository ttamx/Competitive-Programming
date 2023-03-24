#include<bits/stdc++.h>

using namespace std;

const int N=2505;
const int K=1<<18;

int n,q;
vector<int> adj[N],rev[N];
pair<int,int> a[N];
int l[N],r[N];
bool vis[N];
queue<pair<int,int>> qu;

struct maxsegtree{
    int t[K];
    void update(int l,int r,int i,int &x,int &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return -2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}sr;

struct minsegtree{
    int t[K];
    void update(int l,int r,int i,int &x,int &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return 2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}sl,seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    assert(n<=2500);
    for(int i=1;i<=n;i++)l[i]=r[i]=1e9;
    l[1]=1;
    r[n]=1;
    for(int i=1;i<=n;i++){
        auto &[l,r]=a[i];
        cin >> l >> r;
        sl.update(i,l);
        sr.update(i,r);
        for(int j=l;j<=r;j++){
            adj[i].emplace_back(j);
            rev[j].emplace_back(i);
        }
    }
    qu.emplace(0,1);
    vis[1]=true;
    while(!qu.empty()){
        auto [d,u]=qu.front();
        qu.pop();
        for(auto v:rev[u]){
            if(vis[v])continue;
            vis[v]=true;
            l[v]=d+1;
            qu.emplace(d+1,v);
        }
    }
    for(int i=1;i<=n;i++)vis[i]=false;
    qu.emplace(0,n);
    vis[n]=true;
    while(!qu.empty()){
        auto [d,u]=qu.front();
        qu.pop();
        for(auto v:rev[u]){
            if(vis[v])continue;
            vis[v]=true;
            r[v]=d+1;
            qu.emplace(d+1,v);
        }
    }
    for(int i=1;i<=n;i++)seg.update(i,l[i]+r[i]-1);
    cin >> q;
    while(q--){
        int x;
        cin >> x;
        int ans=l[x]+r[x]-1;
        auto [st,ed]=a[x];
        for(int i=1;i<=n;i++){
            ans=min(ans,i+seg.query(st,ed));
            int ll=sl.query(st,ed);
            int rr=sr.query(st,ed);
            st=ll;
            ed=rr;
        }
        cout << (ans<1e9?ans:-1) << '\n';
    }
}