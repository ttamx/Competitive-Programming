#include<bits/stdc++.h>

using namespace std;

const int N=1<<18;

struct node{
    int mn,mx;
};

node merge(node a,node b){
    node c;
    c.mn=min(a.mn,b.mn);
    c.mx=max(a.mx,b.mx);
    return c;
}

struct segtree{
    node tree[N];
    void build(int l,int r,int i){
        if(l==r){
            tree[i]={l,l};
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        tree[i]=merge(tree[i*2],tree[i*2+1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r){
            tree[i]={v,v};
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        tree[i]=merge(tree[i*2],tree[i*2+1]);
    }
    node query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return {(int)2e9,0};
        if(x<=l&&r<=y)return tree[i];
        int m=(l+r)/2;
        return merge(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s;

int n,k;
int a[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    iota(a,a+n,0);
    s.build(0,n-1,1);
    while(k--){
        int o,x,y;
        cin >> o >> x >> y;
        if(o){
            node ans=s.query(0,n-1,1,x,y);
            cout << ((ans.mn==x&&ans.mx==y)?"YES":"NO") << '\n';
        }else{
            swap(a[x],a[y]);
            s.update(0,n-1,1,x,a[x]);
            s.update(0,n-1,1,y,a[y]);
        }
    }
}