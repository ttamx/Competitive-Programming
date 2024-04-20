#include <bits/stdc++.h>
#include "dorm.h"

using namespace std;

using ll = long long;

const int N=3005;
const int M=1e5+5;

int n;
int a[N];
ll base;
vector<tuple<ll,ll,ll>> sub;

ll pw2(ll x){
    return x*x;
}

int cdiv(int a,int b){
    return (a-1)/b+1;
}

ll calc(int i,int x){
    x++;
    ll sz=a[i]/x;
    ll cnt=x-a[i]%x;
    return pw2(sz)*cnt+pw2(sz+1)*(x-cnt);
}

void add(ll dif,ll sz){
    sub.emplace_back(dif,dif*sz,sz);
}

void init(int N,vector<vector<int>> Req){
    n=N;
    for(auto x:Req)a[x[0]+1]++,a[x[1]+2]--;
    for(int i=1;i<=n;i++)a[i]+=a[i-1];
    for(int i=1;i<=n;i++)if(a[i]){
        base+=pw2(a[i]);
        int val=a[i];
        int cnt=0;
        vector<pair<int,int>> vec;
        vec.emplace_back(val,0);
        while(val>1){
            int l=cnt+1,r=a[i]-1;
            while(l<r){
                int m=(l+r)/2;
                if(cdiv(a[i],m+1)<val)r=m;
                else l=m+1;
            }
            val=cdiv(a[i],l+1);
            cnt=l;
            vec.emplace_back(val,cnt);
        }
        for(int j=0;j<vec.size()-1;j++){
            auto [val,cnt]=vec[j];
            int freq=(a[i]-1)%(cnt+1)+1;
            int ok=vec[j+1].second-1-cnt;
            add(calc(i,vec[j+1].second-1)-calc(i,vec[j+1].second),1);
            if(ok)add(pw2(val)*(val-1)-pw2(val-1)*val,ok);
        }
    }
    sort(sub.rbegin(),sub.rend());
    for(int i=1;i<sub.size();i++){
        get<1>(sub[i])+=get<1>(sub[i-1]);
        get<2>(sub[i])+=get<2>(sub[i-1]);
    }
}

long long least_crowded(int P){
    int l=0,r=sub.size();
    while(l<r){
        int m=(l+r)/2;
        if(get<2>(sub[m])>P)r=m;
        else l=m+1;
    }
    ll res=base;
    if(l){
        res-=get<1>(sub[l-1]);
        P-=get<2>(sub[l-1]);
    }
    if(l==sub.size())return res;
    res-=get<0>(sub[l])*P;
    return res;
}