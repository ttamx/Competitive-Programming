#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef tuple<ll,ll,ll> t3;

const int K=1<<19;

struct segtree{
    int t[K],lz[K];
    void pushlz(int l,int r,int i){
        if(lz[i]==-1)return;
        t[i]=lz[i];
        if(l<r)lz[i*2]=lz[i*2+1]=lz[i];
        lz[i]=-1;
    }
    void build(int l,int r,int i){
        if(l==r)return t[i]=0,lz[i]=-1,void();
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    void update(int l,int r,int i,int x,int y,int v){
        pushlz(l,r,i);
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return lz[i]=v,pushlz(l,r,i),void();
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
        t[i]=max(t[i*2],t[i*2+1]);
    }
    int query(int l,int r,int i,int x){
        pushlz(l,r,i);
        if(x<l||r<x)return 0;
        if(l==r)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x),query(m+1,r,i*2+1,x));
    }
}s;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> vec(n+1);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        vec[x].emplace_back(i);
    }
    ll m;
    cin >> m;
    vector<pair<ll,ll>> ran;
    vector<ll> cnt;
    s.build(1,n,1);
    int idx=0;
    ran.emplace_back(1,n);
    cnt.emplace_back(n);
    for(int i=n;i>=0;i--){
        for(auto x:vec[i]){
            int pos=s.query(1,n,1,x);
            auto [l,r]=ran[pos];
            cnt[pos]-=i;
            if(l<x){
                s.update(1,n,1,l,x-1,++idx);
                ran.emplace_back(l,x-1);
                cnt.emplace_back(i);
            }
            if(x<r){
                s.update(1,n,1,x+1,r,++idx);
                ran.emplace_back(x+1,r);
                cnt.emplace_back(i);
            }
        }
    }
    vector<ll> res(n+1);
    for(int i=0;i<=idx;i++){
        auto [l,r]=ran[i];
        res[r-l+1]+=cnt[i];
    }
    ll ans=0;
    for(int i=n;i>=1;i--){
        if(m<=0)break;
        if(m>=i*res[i]){
            m-=i*res[i];
            ans+=(i-1)*res[i];
        }else{
            ll can=m/i;
            m-=i*can;
            ans+=(i-1)*can;
            if(m<=0)break;
            ans+=m-1;
            break;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}