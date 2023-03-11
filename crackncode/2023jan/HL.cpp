#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll N=2e5+5;
const ll K=1<<19;
const ll mod=1e9+7;

ll n,q;
ll h[N],pos[N],id[N];
ll inv2;
ll pw2[N],ipw[N];
ll ans=0;

struct fenwick{
    ll t[N];
    void add(ll i,ll v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    ll read(ll i){
        ll res=0;
        while(i)res+=t[i],i-=i&-i;
        return res;
    }
}f;

struct segtree{
    ll t[K],lz[K];
    void pushlz(ll l,ll r,ll i){
        if(lz[i]>0)t[i]=(t[i]*pw2[lz[i]])%mod;
        else t[i]=(t[i]*ipw[-lz[i]])%mod;
        if(l<r){
            lz[i*2]=(lz[i*2]+lz[i])%mod;
            lz[i*2+1]=(lz[i*2+1]+lz[i])%mod;
        }
        lz[i]=0;
    }
    void sum(ll l,ll r,ll i,ll x,ll v){
        pushlz(l,r,i);
        if(r<x||x<l)return;
        if(l==r)return void(t[i]=(t[i]+v)%mod);
        ll m=(l+r)/2;
        sum(l,m,i*2,x,v);
        sum(m+1,r,i*2+1,x,v);
        t[i]=(t[i*2]+t[i*2+1])%mod;
    }
    void sum(ll x,ll v){
        sum(1,N,1,x,v);
    }
    void update(ll l,ll r,ll i,ll x,ll y,ll v){
        pushlz(l,r,i);
        if(r<x||y<l)return;
        if(x<=l&&r<=y){
            lz[i]+=v;
            pushlz(l,r,i);
            return;
        }
        ll m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=(t[i*2]+t[i*2+1])%mod;
    }
    void update(ll x,ll y,ll v){
        update(1,N,1,x,y,v);
    }
    ll query(ll l,ll r,ll i,ll x,ll y){
        pushlz(l,r,i);
        if(r<x||y<l)return 0;
        if(x<=l&&r<=y)return t[i];
        ll m=(l+r)/2;
        return (query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y))%mod;
    }
    ll query(ll x,ll y){
        return query(1,N,1,x,y);
    }
}sp,sm;

ll binpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res*=a,res%=mod;
        a*=a,a%=mod;
        b/=2;
    }
    return res;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    inv2=binpow(2,mod-2);
    pw2[0]=ipw[0]=1;
    for(ll i=1;i<N;i++)pw2[i]=(pw2[i-1]*2)%mod,ipw[i]=(ipw[i-1]*inv2)%mod;
    cin >> n >> q;
    vector<pair<ll,ll>> in,qr(q);
    for(ll i=1;i<=n;i++){
        cin >> h[i];
        in.push_back({h[i],i});
    }
    for(int i=n+1;i<=n+q;i++){
        cin >> id[i] >> h[i];
        in.push_back({h[i],i});
    }
    sort(in.begin(),in.end());
    for(int i=0;i<n+q;i++)pos[in[i].second]=i+1;
    for(int i=1;i<=n;i++)f.add(pos[i],1);
    for(ll i=1;i<=n;i++){
        ll l=f.read(pos[i]-1),r=f.read(N-1)-f.read(pos[i]);
        sp.sum(pos[i],(h[i]*pw2[l])%mod);
        sm.sum(pos[i],(h[i]*pw2[r])%mod);
    }
    for(int i=n+1;i<=n+q;i++){
        ll a=id[i];
        ll l=f.read(pos[a]-1),r=f.read(N-1)-f.read(pos[a]);
        f.add(pos[a],-1);
        sp.sum(pos[a],(mod-((h[a]*pw2[l])%mod))%mod);
        sm.sum(pos[a],(mod-((h[a]*pw2[r])%mod))%mod);
        sp.update(pos[a]+1,N,-1);
        sm.update(1,pos[a]-1,-1);
        h[a]=h[i];
        pos[a]=pos[i];
        f.add(pos[a],1);
        sp.update(pos[a]+1,N,1);
        sm.update(1,pos[a]-1,1);
        l=f.read(pos[a]-1),r=f.read(N-1)-f.read(pos[a]);
        sp.sum(pos[a],(h[a]*pw2[l])%mod);
        sm.sum(pos[a],(h[a]*pw2[r])%mod);
        ll ans=(sp.t[1]-sm.t[1]+mod)%mod;
        assert(ans>=0&&ans<mod);
        cout << ans << '\n';
    }
}