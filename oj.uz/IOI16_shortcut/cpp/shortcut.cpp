#include "shortcut.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const ll X=1e15+1e9;
const ll INF=1e18;

int n,c;
ll a[N],d[N];
vector<int> ord1,ord2;

bool check(ll k){
    ll l1=-INF,r1=INF; // x+y
    ll l2=-INF,r2=INF; // x-y
    int mx11=-1,mx12=-1,mx21=-1,mx22=-1; // d[i]+a[i],d[i]-a[i]
    auto ord=ord2;
    for(auto i:ord1){
        while(!ord.empty()&&d[i]+a[i]+d[ord.back()]-a[ord.back()]>k){
            int j=ord.back();
            ord.pop_back();
            if(mx12==-1||d[j]+a[j]>d[mx12]+a[mx12])mx12=j;
            if(mx11==-1||d[mx12]+a[mx12]>d[mx11]+a[mx11])swap(mx11,mx12);
            if(mx22==-1||d[j]-a[j]>d[mx22]-a[mx22])mx22=j;
            if(mx21==-1||d[mx22]-a[mx22]>d[mx21]-a[mx21])swap(mx21,mx22);
        }
        auto get1=[&](){
            if(mx11!=-1&&mx11!=i)return d[mx11]+a[mx11];
            return mx12!=-1?d[mx12]+a[mx12]:-INF;
        };
        auto get2=[&](){
            if(mx21!=-1&&mx21!=i)return d[mx21]-a[mx21];
            return mx22!=-1?d[mx22]-a[mx22]:-INF;
        };
        l1=max(l1,d[i]+a[i]+get1()-k+c);
        r1=min(r1,-(d[i]-a[i])-get2()+k-c);
        l2=max(l2,d[i]+a[i]+get2()-k+c);
        r2=min(r2,-(d[i]-a[i])-get1()+k-c);
    }
    if(l1>r1||l2>r2)return false;
    int l=n-1,r=0;
    for(int i=0;i<n;i++){
        while(l>0&&a[i]+a[l-1]>=l1)l--;
        while(r<n&&a[i]-a[r]>r2)r++;
        int p=max(l,r);
        if(p<i&&a[i]+a[p]<=r1&&a[i]-a[p]>=l2)return true;
    }
    return false;
}

ll find_shortcut(int _n,vector<int> _l,vector<int> _d,int _c){
    n=_n,c=_c;
    for(int i=0;i+1<n;i++)a[i+1]=a[i]+_l[i];
    for(int i=0;i<n;i++)d[i]=_d[i];
    ord1.resize(n);
    iota(ord1.begin(),ord1.end(),0);
    ord2=ord1;
    sort(ord1.begin(),ord1.end(),[&](int i,int j){return d[i]+a[i]<d[j]+a[j];});
    sort(ord2.begin(),ord2.end(),[&](int i,int j){return d[i]-a[i]<d[j]-a[j];});
    ll l=0LL,r=X;
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    return l;
}
