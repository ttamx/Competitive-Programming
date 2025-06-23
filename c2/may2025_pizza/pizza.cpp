#include "pizza.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

pair<ll,ll> mul(ll a,ll b){
    ll a1=a>>30,a2=a&((1LL<<30)-1);
    ll b1=b>>30,b2=b&((1LL<<30)-1);
    ll x=a1*b1,y=a1*b2+b1*a2;
    ll z=a2*b2+((y&((1LL<<30)-1))<<30);
    return {x+(y>>30)+(z>>60),z&((1LL<<60)-1)};
}

struct Frac{
    ll a,b;
    friend Frac operator-(const Frac &l,const Frac &r){
        return Frac{l.a*r.b-r.a*l.b,l.b*r.b};
    }
    friend bool operator==(const Frac &l,const Frac &r){
        return mul(l.a,r.b)==mul(l.b,r.a);
    }
    bool operator<(const Frac &o){
        return a*o.b<b*o.a;
    }
};

int countangles(int n,vector<int> b,vector<int> a){
    vector<Frac> c;
    for(int i=0;i<n;i++)c.emplace_back(Frac{a[i],b[i]});
    sort(c.begin(),c.end());
    c.emplace_back(Frac{c[0].a+c[0].b,c[0].b});
    for(int i=0;i<n;i++)c[i]=c[i+1]-c[i];
    c.pop_back();
    c.insert(c.end(),c.begin(),c.end());
    int m=2*n;
    vector<int> z(m);
    z[0]=m;
    for(int i=1,l=0,r=0;i<m;i++){
        if(i<r)z[i]=min(z[i-l],r-i);
        while(i+z[i]<m&&c[z[i]]==c[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    int ans=0;
    for(int i=0;i<n;i++)if(z[i]>=n)ans++;
    return ans;
}