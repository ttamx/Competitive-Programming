#include "bombs.h"
#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=2e5+5;

int n;
multiset<ll> l,r;
ll lzl,lzr;
ll pre=-1,mn;

void initialize(int N){
    n=N;
}

long long max_hp_loss(int X, int T,int A, int P){
    mn+=A;
    if(pre!=-1){
        ll d=(T-pre)*P;
        lzl-=d;
        lzr+=d;
    }
    pre=T;
    if(l.empty()||r.empty()){
        l.emplace(X);
        r.emplace(X);
    }else if(X<=*l.rbegin()+lzl){
        mn-=*l.rbegin()+lzl-X;
        r.emplace(*l.rbegin()+lzl-lzr);
        l.erase(prev(l.end()));
        l.emplace(X-lzl);
        l.emplace(X-lzl);
    }else if(X>=*r.begin()+lzr){
        mn-=X-(*r.begin()+lzr);
        l.emplace(*r.begin()+lzr-lzl);
        r.erase(r.begin());
        r.emplace(X-lzr);
        r.emplace(X-lzr);
    }else{
        l.emplace(X-lzl);
        r.emplace(X-lzr);
    }
    return mn;
}
