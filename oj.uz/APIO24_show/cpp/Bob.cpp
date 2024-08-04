#include <bits/stdc++.h>
#include "Bob.h"

using namespace std;

using i128 = __int128_t;

long long Bob(vector<pair<int,int>> e){
    const i128 LIM=1e18;
    auto extgcd=[&](i128 a,i128 b){
        i128 u=1,v=0,q;
        while(b){
            q=a/b;
            a-=q*b,u-=q*v;
            swap(a,b),swap(u,v);
        }
        return make_tuple(a,u,v);
    };
    i128 a=0,m=0;
    for(auto [u,v]:e){
        if(m>LIM)break;
        u--,v--;
        if(u>v)swap(u,v);
        if(m==0){
            a=u,m=v;
            continue;
        }
        auto [g,x,y]=extgcd(m,v);
        a=a+x*(u-a)/g%(v/g)*m;
        m=m/g*v;
        a%=m;
        if(a<0)a+=m;
    }
    return a;
}