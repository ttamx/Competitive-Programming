#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<18;

typedef long long ll;

int n,m;
vector<int> pts[N];
vector<pair<int,int>> qr[N];
int ans[N];

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        t[i]=2e9;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,N,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(r<x||x<l)return;
        if(l==r)return void(t[i]=min(t[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,N,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(r<x||y<l)return 2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,N,1,x,y);
    }
}s1,s2;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        pts[x].emplace_back(y);
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin >> x >> y;
        qr[x].emplace_back(y,i);
        ans[i]=2e9;
    }
    s1.build();
    s2.build();
    for(int i=1;i<N;i++){
        for(auto x:pts[i]){
            s1.update(x,-x-i);
            s2.update(x,x-i);
        }
        for(auto [x,y]:qr[i]){
            ans[y]=min(ans[y],x+i+s1.query(1,x));
            ans[y]=min(ans[y],-x+i+s2.query(x,N));
        }
    }
    s1.build();
    s2.build();
    for(int i=N-1;i>=1;i--){
        for(auto x:pts[i]){
            s1.update(x,-x+i);
            s2.update(x,x+i);
        }
        for(auto [x,y]:qr[i]){
            ans[y]=min(ans[y],x-i+s1.query(1,x));
            ans[y]=min(ans[y],-x-i+s2.query(x,N));
        }
    }
    for(int i=1;i<=m;i++)cout << ans[i] << "\n";
}