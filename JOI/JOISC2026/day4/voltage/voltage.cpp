#include "voltage.h"
#include<bits/stdc++.h>

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool solve(int n,int m){
    vector<int> cur(n,1),ord;
    vector<int> cands(n);
    iota(cands.begin(),cands.end(),0);
    shuffle(cands.begin(),cands.end(),rng);
    auto erase=[&](int x){
        cands.erase(find(cands.begin(),cands.end(),x));
    };
    for(int i=0;i<n;i++){
        auto tmp=cur;
        tmp[i]=0;
        if(query(cur,tmp)==0){
            ord.emplace_back(i);
            erase(i);
        }
    }
    for(int i=0;i<ord.size();i++){
        int u=ord[i];
        auto check=[&](int l,int r){
            auto tmp=cur;
            for(int i=l;i<r;i++)tmp[cands[i]]=0;
            auto tmp2=tmp;
            tmp2[u]=0;
            return query(tmp2,tmp)==1;
        };
        vector<int> a;
        function<void(int,int)> dnc=[&](int l,int r){
            if(l+1==r){
                a.emplace_back(cands[l]);
                return;
            }
            int m=(l+r)/2;
            if(check(l,m)){
                dnc(l,m);
                if(check(m,r))dnc(m,r);
            }else{
                dnc(m,r);
            }
        };
        if(check(0,cands.size()))dnc(0,cands.size());
        cur[u]=0;
        for(auto x:a){
            answer(u,x);
            auto tmp=cur;
            tmp[x]=0;
            if(query(cur,tmp)==0){
                ord.emplace_back(x);
                erase(x);
            }
        }
    }
    return ord.size()==n;
}
