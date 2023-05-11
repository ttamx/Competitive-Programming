#include<bits/stdc++.h>

using namespace std;

//SEGMENT TREE
template<class T>
struct segtree{
    const int n;
    const T I=0;//identity
    vector<T> t;
    segtree(int n):n(n),t(n*4,I){}
    T merge(T l,T r){
        //do something;
        return max(l,r);
    }
    void build(int l,int r,int i,vector<T> &a){
        if(l==r)return void(t[i]=a[l]);
        int m=(l+r)/2;
        build(l,m,i*2,a);
        build(m+1,r,i*2+1,a);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void build(vector<T> &a){
        build(1,n,1,a);
    }
    void update(int l,int r,int i,int &x,T &v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=merge(t[i*2],t[i*2+1]);
    }
    void update(int x,T v){
        update(1,n,1,x,v);
    }
    T query(int l,int r,int i,int &x,int &y){
        if(y<l||r<x)return I;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    T query(int x,int y){
        return query(1,n,1,x,y);
    }
};
//--------------------------------------------------------

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1);
    for(int i=1;i<=n;i++)cin >> a[i];
    segtree<int> s(n);
    s.build(a);
    vector<int> b(n+1);
    for(int i=1;i<=n;i++)b[i]=max(b[i-1],a[i]+i);
    int idx=1;
    int ans=0;
    for(int i=3;i<=n;i++){
        while(i-idx>=3&&b[idx+1]+s.query(idx+2,i-1)>=b[idx]+s.query(idx+1,i-1))idx++;
        ans=max(ans,a[i]-i+b[idx]+s.query(idx+1,i-1));
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}