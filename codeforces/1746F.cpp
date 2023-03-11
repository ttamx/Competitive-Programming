#include<bits/stdc++.h>

using namespace std;

const int K=1<<20;

struct segtree{
    int tree[K];
    void build(int l,int r,int i){
        if(l==r){
            tree[i]=0;
            return;
        }
        int m=(l+r)>>1;
        build(l,m,i<<1);
        build(m+1,r,i<<1|1);
        tree[i]=gcd(tree[i<<1],tree[i<<1|1]);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||x>r)return;
        if(l==r){
            tree[i]=v;
            return;
        }
        int m=(l+r)>>1;
        update(l,m,i<<1,x,v);
        update(m+1,r,i<<1|1,x,v);
        tree[i]=gcd(tree[i<<1],tree[i<<1|1]);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return tree[i];
        int m=(l+r)>>1;
        return gcd(query(l,m,i<<1,x,y),query(m+1,r,i<<1|1,x,y));
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        s.update(1,n,1,i,x);
    }
    while(q--){
        int o;
        cin >> o;
        if(o==1){
            int x,y;
            cin >> x >> y;
            s.update(1,n,1,x,y);
        }else{
            int l,r,k;
            cin >> l >> r >> k;
            cout << s.query(1,n,1,l,r) << '\n';
            if(s.query(1,n,1,l,r)%k==0)cout << "YES\n";
            else cout << "NO\n";
        }
    }
}