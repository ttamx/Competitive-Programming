#include<bits/stdc++.h>

using namespace std;

const int N=2505;
const int K=1<<13;
const int MOD=1e9+7;

int n,m;
int h[N],hh[N],ps[N];
int dp[N][N];
int add[N];
int ans;

int norm(int x){
    return x>=MOD?x-MOD:x;
}

int ub(int x){
    return upper_bound(hh+1,hh+n+1,x)-hh;
}

int lb(int x){
    return lower_bound(hh+1,hh+n+1,x)-hh;
}

struct segtree{
    int t[K];
    bool lz[K];
    void push(int l,int r,int i){
        if(!lz[i])return;
        lz[i]=false;
        t[i]=0;
        if(l<r){
            lz[i*2]=lz[i*2+1]=true;
        }
    }
    void clear(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return;
        if(l<=x&&y<=r)return lz[i]=true,push(l,r,i);
        int m=(l+r)/2;
        clear(l,m,i*2,x,y);
        clear(m+1,r,i*2+1,x,y);
        t[i]=norm(t[i*2]+t[i*2+1]);
    }
    void clear(int x,int y){
        clear(1,n,1,x,y);
    }
    void update(int l,int r,int i,int x,int v){
        push(l,r,i);
        if(x<l||r<x)return;
        if(l==r)return void(t[i]=norm(t[i]+v));
        int m=(l+r)/2;
        update(l,m,i*2,x,v);
        update(m+1,r,i*2+1,x,v);
        t[i]=norm(t[i*2]+t[i*2+1]);
    }
    void update(int x,int v){
        update(1,n,1,x,v);
    }
    int query(int l,int r,int i,int x,int y){
        push(l,r,i);
        if(y<l||r<x)return 0;
        if(x<=l&&r<=y)return t[i];
        int m=(l+r)/2;
        return norm(query(l,m,i*2,x,y)+query(m+1,r,i*2+1,x,y));
    }
    int query(int x,int y){
        return query(1,n,1,x,y);
    }
}s1[N],s2[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++)cin >> h[i],hh[i]=h[i];
    sort(hh+1,hh+n+1);
    for(int i=1;i<=n;i++)ps[i]=lb(h[i]);
    dp[0][0]=1;
    for(int i=2,p=0;i<=n;i++){
        for(int j=0;j<i-1;j++)add[j]=dp[j][0];
        int l=lb(h[i]-m),r=ub(h[i]+m)-1;
        for(int k=0;k<i-2;k++)add[k]=norm(add[k]+s1[k].query(l,r));
        for(int j=1;j<i-1;j++)add[j]=norm(add[j]+s2[j].query(l,r));
        if(abs(h[i]-h[i-1])>m){
            for(int j=0;j<i;j++)s1[j].clear(1,n);
            for(int j=0;j<i;j++)s2[j].clear(1,n);
            for(;p<i-1;p++)for(int k=0;k<i;k++)dp[p][k]=0;
        }
        for(int j=0;j<i-1;j++){
            dp[i-1][j]=norm(dp[i-1][j]+add[j]);
            s1[j].update(ps[i-1],add[j]);
            s2[i-1].update(ps[j],add[j]);
            add[j]=0;
        }
    }
    for(int j=1;j<n;j++){
        for(int k=1;k<j;k++)ans=norm(ans+dp[j][k]);
        ans=norm(ans+dp[j][0]);
    }
    ans=(1ll*ans*2+dp[0][0])*3%MOD;
    cout << ans;
}