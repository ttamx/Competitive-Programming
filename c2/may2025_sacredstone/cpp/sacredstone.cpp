#include "sacredstone.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

ll sacredstone(int n,vector<int> a,vector<int> c){
    using V = vector<ll>;
    using T = array<array<V,3>,3>;
    auto merge=[&](V a,V b)->V {
        for(int i=a.size()-1;i>0;i--)a[i]-=a[i-1];
        for(int i=b.size()-1;i>0;i--)b[i]-=b[i-1];
        V c{a[0]+b[0]};
        int i=1,j=1;
        while(i<a.size()||j<b.size()){
            if(j==b.size()||(i<a.size()&&a[i]>b[j]))c.emplace_back(a[i++]);
            else c.emplace_back(b[j++]);
        }
        for(int i=1;i<c.size();i++)c[i]+=c[i-1];
        return c;
    };
    auto upd=[&](V &a,const V &b){
        for(int i=0;i<b.size();i++){
            if(i==a.size())a.emplace_back(b[i]);
            else a[i]=max(a[i],b[i]);
        }
    };
    vector<pair<int,int>> pos;
    pos.emplace_back(0,0);
    pos.emplace_back(1,2);
    pos.emplace_back(2,1);
    function<T(int,int)> rec=[&](int l,int r)->T {
        T res{};
        if(l==r){
            res[0][0]={0};
            res[0][1]={a[l]};
            res[0][2]={-a[l]};
            res[1][0]={a[l]};
            res[2][0]={-a[l]};
        }else{
            int m=(l+r)/2;
            T vl=rec(l,m);
            T vr=rec(m+1,r);
            for(int i=0;i<3;i++){
                for(int j=0;j<3;j++){
                    upd(res[i][j],vl[i][j]);
                    upd(res[i][j],vr[i][j]);
                    for(auto [x,y]:pos){
                        if(vl[i][x].empty()||vr[y][j].empty())continue;
                        V a=merge(vl[i][x],vr[y][j]);
                        if(x+y==3)a.insert(a.begin(),-INF);
                        upd(res[i][j],a);
                    }
                }
            }
        }
        return res;
    };
    ll ans=0;
    T b=rec(0,n-1);
    for(int i=0;i<b[0][0].size();i++)ans=max(ans,b[0][0][i]+c[n-2*i]);
    for(int i=0;i<b[0][1].size();i++)ans=max(ans,b[0][1][i]+c[n-2*i-1]);
    return ans;
}