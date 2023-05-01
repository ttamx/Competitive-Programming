#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int N=2e5+5;
const int K=1<<19;
 
int n;
ll sum,ans;
ll a[N],qs[N],dp[N];
 
struct line{
    ll m,c;
    line(ll m=0,ll c=-1e18):m(m),c(c){}
    ll get(ll x){
        return x*m+c;
    }
};
 
struct LiChaoTree{
    line t[K];
    void add(int l,int r,int i,line x){
        if(l==r){
            if(x.get(l)>t[i].get(l))t[i]=x;
            return;
        }
        int m=(l+r)/2;
        if(x.m<t[i].m)swap(x,t[i]);
        if(x.get(m)>t[i].get(m)){
            swap(x,t[i]);
            add(l,m,i*2,x);
        }else{
            add(m+1,r,i*2+1,x);
        }
    }
    void add(line x){
        add(1,n,1,x);
    }
    ll read(int l,int r,int i,int x){
        if(x<l||r<x)return -1e18;
        if(l==r)return t[i].get(x);
        int m=(l+r)/2;
        return max({t[i].get(x),read(l,m,i*2,x),read(m+1,r,i*2+1,x)});
    }
    ll read(int x){
        return read(1,n,1,x);
    }
}l1,l2;
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++)qs[i]=qs[i-1]+a[i];
    for(int i=1;i<=n;i++)sum+=a[i]*i;
    ans=sum;
    for(int i=1;i<=n;i++){
        ans=max(ans,l1.read(i)-qs[i]);
        l1.add({a[i],sum-a[i]*i+qs[i]});
    }
    for(int i=n;i>=1;i--){
        ans=max(ans,l2.read(i)-qs[i-1]);
        l2.add({a[i],sum-a[i]*i+qs[i-1]});
    }
    cout << ans;
} 