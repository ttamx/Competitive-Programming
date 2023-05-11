#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=3005;

int n;
ll a[N];
ll sum=0;

ll calc(ll val,ll p){
    p++;
    if(p>=val)return val;
    ll num=val/p;
    ll rem=val-num*p;
    return rem*((num+1)*(num+1))+(p-rem)*num*num;
}

void init(int N,vector<vector<int> > Req){
    n=N;
    for(auto v:Req){
        int l=v[0],r=v[1];
        l++,r++;
        a[l]++;
        a[r+1]--;
        sum+=r-l+1;
    }
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    sort(a+1,a+n+1,greater<ll>());
}
ll least_crowded(int P){
    int l=1,r=300000;
    while(l<r){
        int m=(l+r)/2;
        int cnt=0;
        for(int i=1;i<=n;i++){
            cnt+=(a[i]-1)/m;
        }
        if(cnt<=P)r=m;
        else l=m+1;
    }
    cerr << l << " ";
    ll res=0;
    for(int i=1;i<=n;i++){
        int d=(a[i]-1)/l;
        res+=calc(a[i],d);
    }
    return res;
}
