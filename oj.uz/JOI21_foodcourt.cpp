#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=250005;
const int K=1<<19;
const ll inf=1e18;

int n,m,q;
ll c[N],k[N],b[N];
vector<int> qr1[N],qr2[N],qr3[N];
int ans[N];

struct minsegtree{
    ll t[K],lz[K];
    void pushlz(int l,int r,int i){
        t[i]+=lz[i];
        if(l<r){
            lz[i*2]+=lz[i];
            lz[i*2+1]+=lz[i];
        }
        lz[i]=0;
    }
    void update(int l,int r,int i,int x,int y,ll v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]+=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=min(t[i*2],t[i*2+1]);
    }
    void update(int x,int y,ll v){
        update(1,q,1,x,y,v);
    }
    ll query(int l,int r,int i,int x,int y){
        pushlz(l,r,i);
        if(y<l||r<x)return inf;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return min(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
    ll query(int x,int y){
        return query(1,q,1,x,y);
    }
}s;

struct sumsegtree{
    ll t[K];
    void update(int l,int r,int i,int x,ll v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]+=v);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]+t[i*2+1];
    }
    void update(int x,ll v){
        update(1,q,1,x,v);
    }
    int query(int l,int r,int i,ll v){
        if(l==r)return t[i]>=v?l:0;
        int m=(l+r)/2;
        if(t[i*2]>=v)return query(l,m,i*2,v);
        return query(m+1,r,i*2+1,v-t[i*2]);
    }
    int query(ll v){
        return query(1,q,1,v);
    }
}ord;

struct fenwick{
    ll t[N];
    void add(int i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(int i){
        ll res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> q;
    for(int i=1;i<=q;i++){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            cin >> l >> r >> c[i] >> k[i];
            qr1[l].emplace_back(i);
            qr1[r+1].emplace_back(-i);
        }else if(t==2){
            int l,r;
            cin >> l >> r >> k[i];
            qr2[l].emplace_back(i);
            qr2[r+1].emplace_back(-i);
        }else{
            int a;
            cin >> a >> b[i];
            qr3[a].emplace_back(i);
        }
    }
    for(int i=1;i<=n;i++){
        for(auto j:qr1[i]){
            if(j>0){
                s.update(j,q,k[j]);
                ord.update(j,k[j]);
            }else{
                j=-j;
                s.update(j,q,-k[j]);
                ord.update(j,-k[j]);
            }
        }
        for(auto j:qr2[i]){
            if(j>0){
                s.update(j,q,-k[j]);
                f.add(j,k[j]);
            }else{
                j=-j;
                s.update(j,q,k[j]);
                f.add(j,-k[j]);
            }
        }
        for(auto j:qr3[i]){
            ll val=f.read(j)+min(0ll,s.query(1,j))+b[j];
            auto id=ord.query(val);
            ans[j]=c[id>j?0:id];
        }
    }
    for(int i=1;i<=q;i++)if(b[i])cout << ans[i] << "\n";
}