#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int K=1<<20;
const ll inf=1e18;

struct segtree{
    ll t[K];
    void build(int l,int r,int i){
        t[i]=-inf;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void update(int l,int r,int i,int x,ll v){
        if(x<l||r<x)return;
        t[i]=max(t[i],v);
        if(l==r)return;
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
    }
    ll query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return -inf;
        if(x<=l&r<=y)return t[i];
        int m=(l+r)/2;
        return max(query(l,m,i*2,x,y),query(m+1,r,i*2+1,x,y));
    }
}s1,s2;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n),c(n),pa(n),pb(n);
    map<ll,int> mp;
    for(auto &x:a)cin >> x,mp[x];
    for(auto &x:b)cin >> x,mp[x];
    int k=0;
    for(auto &[x,y]:mp)y=++k;
    ll sum=0;
    for(int i=0;i<n;i++){
        pa[i]=mp[a[i]];
        pb[i]=mp[b[i]];
        c[i]=llabs(a[i]-b[i]);
        sum+=c[i];
    }
    ll ans=sum;
    vector<pair<ll,int>> vec;
    for(int i=0;i<n;i++)vec.emplace_back(a[i],i);
    sort(vec.begin(),vec.end());
    vector<int> ord(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return b[i]<b[j];
    });
    s1.build(1,k,1);
    s2.build(1,k,1);
    for(int j=0,p=0;j<n;j++){
        int i=ord[j];
        while(p<n&&vec[p].first<=b[i]){
            int id=vec[p++].second;
            s1.update(1,k,1,pb[id],-a[id]-c[id]-b[id]);
            s2.update(1,k,1,pb[id],-a[id]-c[id]+b[id]);
        }
        ans=max(ans,sum-c[i]+b[i]+a[i]+s1.query(1,k,1,1,pa[i]));
        ans=max(ans,sum-c[i]+b[i]-a[i]+s2.query(1,k,1,pa[i],k));
    }
    s1.build(1,k,1);
    s2.build(1,k,1);
    for(int j=n-1,p=n-1;j>=0;j--){
        int i=ord[j];
        while(p>=0&&vec[p].first>=b[i]){
            int id=vec[p--].second;
            s1.update(1,k,1,pb[id],a[id]-c[id]-b[id]);
            s2.update(1,k,1,pb[id],a[id]-c[id]+b[id]);
        }
        ans=max(ans,sum-c[i]-b[i]+a[i]+s1.query(1,k,1,1,pa[i]));
        ans=max(ans,sum-c[i]-b[i]-a[i]+s2.query(1,k,1,pa[i],k));
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}