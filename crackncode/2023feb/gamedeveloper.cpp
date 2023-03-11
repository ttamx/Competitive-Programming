#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;
const int K=1<<19;

int n;
int pos[N];
ll a[N],dp[N];

struct line{
    ll m,c;
    ll get(ll x){
        return m*x+c;
    }
}lct[K];

bool vis[K];

void add(int l,int r,int i,line x){
    if(!vis[i]){
        lct[i]=x;
        vis[i]=true;
        return;
    }
    if(l==r){
        if(lct[i].get(l)<x.get(l))lct[i]=x;
        return;
    }
    int m=(l+r)/2;
    if(lct[i].m>x.m)swap(lct[i],x);
    if(lct[i].get(m)<x.get(m)){
        swap(lct[i],x);
        add(l,m,i*2,x);
    }else{
        add(m+1,r,i*2+1,x);
    }
}

void add(line x){
    add(1,n,1,x);
}

ll get(int l,int r,int i,ll x){
    if(!vis[i]||r<x||x<l)return -1e18;
    int m=(l+r)/2;
    if(l==r)return lct[i].get(x);
    return max({lct[i].get(x),get(l,m,i*2,x),get(m+1,r,i*2+1,x)});
}

ll get(ll x){
    return get(1,n,1,x);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)dp[i]=dp[i-1]+a[i];
    ll ans=0;
    for(int i=n;i>=1;i--){
        ans=max(ans,get(i)+dp[i-1]);;
        add({-a[i],a[i]*i-dp[i-1]});
    }
    cout << ans;
}