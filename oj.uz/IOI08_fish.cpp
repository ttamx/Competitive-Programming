#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;
const int K=1<<20;

int n,k,mod;
pair<int,int> a[N];
int b[N],ord[N],last[N],nxt[N];
bool ok[N];
int cnt,ans;

struct SegTree{
    int t[K];
    void build(int l,int r,int i){
        t[i]=1;
        if(l==r)return;
        int m=(l+r)/2;
        build(l,m,i*2);
        build(m+1,r,i*2+1);
    }
    void build(){
        build(1,k,1);
    }
    void update(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=(t[i]+v)%mod);
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=t[i*2]*t[i*2+1]%mod;
    }
    void update(int x,int v){
        update(1,k,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        if(y<l||r<x)return 1;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return query(l,m,i*2,x,y)*query(m+1,r,i*2+1,x,y)%mod;
    }
    int query(int x,int y){
        return query(1,k,1,x,y);
    }
}seg;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k >> mod;
    for(int i=1;i<=n;i++)cin >> a[i].first >> a[i].second;
    sort(a+1,a+n+1);
    cnt=k;
    for(int i=n;i>=1;i--){
        auto [l,t]=a[i];
        if(!ord[t]){
            b[cnt]=l;
            ord[t]=cnt;
            last[t]=l;
            ok[i]=true;
            cnt--;
        }
        nxt[i]=last[t];
        last[t]=l;
    }
    seg.build();
    for(int i=1,j=1;i<=n;i++)if(ok[i]){
        auto [l,t]=a[i];
        while(j<=n&&l>=a[j].first*2){
            int x=a[j].second;
            seg.update(ord[x],1);
            last[x]=nxt[j];
            j++;
        }
        int id=lower_bound(b+1,b+k+1,last[t]*2)-b-1;
        ans+=seg.query(1,ord[t]);
        ans+=mod+seg.query(1,ord[t]-1)*(seg.query(ord[t]+1,id)-1);
        ans%=mod;
    }
    cout << ans;
}