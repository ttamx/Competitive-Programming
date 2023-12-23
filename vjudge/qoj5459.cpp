#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6;
const int K=1<<21;

int n,k;
queue<int> q[N];
int l[N],r[N];
ll ans;

struct segtree{
    struct node{
        ll val,freq;
        node():val(0),freq(1){}
        node(ll val,ll freq):val(val),freq(freq){}
        friend node operator+(node l,node r){
            if(l.val<r.val)return l;
            if(r.val<l.val)return r;
            return node(l.val,l.freq+r.freq);
        }
    }t[K];
    ll lz[K];
    void pushlz(int l,int r,int i){
        t[i].val+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void build(int l,int r,int i){
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=t[i*2]+t[i*2+1];
    }
    void build(){
        build(1,n,1);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,int y,ll v){
        update(1,n,1,x,y,v);
    }
}s;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    s.build();
    for(int i=1;i<=n;i++){
        int t;
        cin >> t;
        if(q[t].empty())q[t].emplace(0);
        q[t].emplace(i);
        if(q[t].size()>k){
            q[t].pop();
            s.update(l[t],r[t],-1);
            l[t]=r[t]+1;
            r[t]=q[t].front();
            s.update(l[t],r[t],1);
        }
        if(s.t[1].val==0)ans+=s.t[1].freq-(n-i);
    }
    cout << ans << "\n";
}