#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int K=1<<21;

int n,q;
int a[N],sz[N];
ll ans=0;

struct Segtree{
    ll sum[K],sz[K];
    int lz[K];
    void apply(int i){
        lz[i]^=1;
        sum[i]=sz[i]-sum[i];
    }
    void push(int i){
        if(lz[i]){
            apply(i*2);
            apply(i*2+1);
            lz[i]=0;
        }
    }
    void build(int l,int r,int i){
        if(l==r){
            if(a[l]!=-1){
                sum[i]=a[l];
                sz[i]=1;
            }
            return;
        }
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        sum[i]=sum[i*2]+sum[i*2+1];
        sz[i]=sz[i*2]+sz[i*2+1];
    }
    void toggle(int l,int r,int i,int x,int y){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return apply(i);
        int m=(l+r)/2;
        push(i);
        toggle(l,m,i*2,x,y);
        toggle(m+1,r,i*2+1,x,y);
        sum[i]=sum[i*2]+sum[i*2+1];
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=0;i<n;i++){
        int p;
        cin >> a[i] >> p;
        ans+=p;
    }
    seg.build(0,n-1,1);
    while(q--){
        char op;
        cin >> op;
        if(op=='C'){
            ll x;
            cin >> x;
            ans+=x*seg.sum[1];
        }else{
            int l,r;
            cin >> l >> r;
            seg.toggle(0,n-1,1,l,r);
        }
    }
    cout << ans << "\n";
}