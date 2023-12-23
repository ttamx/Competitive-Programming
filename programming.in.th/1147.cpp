#include<bits/stdc++.h>

using namespace std;

const int N=3e5+5;
const int K=(1<<19)+5;

int n,q;

struct segtree{
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
        if(y<l||r<x)return -1e9;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    while(q--){
        char o;
        int x,y;
        cin >> o >> x >> y;
        if(o=='U')s.update(x,y);
        else cout << s.query(x,y) << '\n';
    }
}