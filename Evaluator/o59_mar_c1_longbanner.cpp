#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;
const int K=1<<19;

int n,h,l;
int x[N],y[N];
map<int,int> mp;

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=0);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> h >> l;
    for(int i=1;i<=n;i++){
        cin >> x[i] >> y[i];
        mp[y[i]];
    }
    int idx=0;
    for(auto &[x,y]:mp)y=++idx;
    idx=1;
    int ans=0;
    for(int i=1;i<=n;i++){
        while(x[i]-x[idx]>h){
            for(int j=0;j<=l;j++)s.update(mp[y[idx]-j],-1);
            idx++;
        }
        for(int j=0;j<=l;j++)s.update(mp[y[i]-j],1);
        ans=max(ans,s.t[1]);
    }
    cout << ans;
}