#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e5+5;
const int K=1<<18;

int n,q;
ll a[N];

struct segtree{
    ll s[K],lz[K];
    void pushlz(int l,int r,int i){
        if(!lz[i])return;
        s[i]+=lz[i]*(r-l+1);
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(r<x||l>y)return;
        if(x<=l&&r<=y){
            lz[i]+=v;
            pushlz(l,r,i);
            return;
        }
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        s[i]=s[i*2]+s[i*2+1];
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(r<x||l>y)return 0;
        if(x<=l&&r<=y)return s[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++)cin >> a[i];
    while(q--){
        int o;
        cin >> o;
        if(o==1){
            int l,r,w;
            cin >> l >> r >> w;
            if(l-w+1>0){
                s.update(1,n,1,l-w+1,l,1);
            }else{
                s.update(1,n,1,1,1,w-l);
                s.update(1,n,1,1,l,1);
            }
            if(r+w<=n){
                s.update(1,n,1,r+1,r+w,-1);
            }else{
                s.update(1,n,1,r+1,n,-1);
            }
        }else{
            int x;
            cin >> x;
            ll ans=a[x]+s.query(1,n,1,1,x);
            cout << ans << '\n';
            a[x]-=ans;
        }
    }
}