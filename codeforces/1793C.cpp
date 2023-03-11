#include<bits/stdc++.h>

using namespace std;

const int K=1<<19;

struct segtree{
    int t[K];
    void build(int l,int r,int i){
        if(l==r)return void(t[i]=-2e9);
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return -2e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    vector<int> l(n+1),r(n+1);
    s.build(1,n,1);
    for(int i=1;i<=n;i++){
        l[i]=max(0,min(s.query(1,n,1,1,a[i]),s.query(1,n,1,a[i],n)));
        s.update(1,n,1,a[i],i);
    }
    s.build(1,n,1);
    for(int i=n;i>=1;i--){
        r[i]=min(n+1,-min(s.query(1,n,1,1,a[i]),s.query(1,n,1,a[i],n)));
        s.update(1,n,1,a[i],-i);
    }
    s.build(1,n,1);
    for(int i=1;i<=n;i++)s.update(1,n,1,i,l[i]);
    for(int i=1;i<=n;i++){
        if(r[i]>n)continue;
        int lo=r[i],hi=n+1;
        while(lo<hi){
            int mid=(lo+hi)/2;
            if(s.query(1,n,1,r[i],mid)>=i)hi=mid;
            else lo=mid+1;
        }
        if(lo>n)continue;
        cout << i << ' ' << lo << '\n';
        return;
    }
    cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}