#include<bits/stdc++.h>
#include "alienlang.h"

using namespace std;

using ll = long long;

vector<int> NAF(int x){
    vector<int> res;
    while(x){
        int v=x%2?2-x%4:0;
        res.emplace_back(v);
        x=(x-v)/2;
    }
    return res;
}

int sgn(int x){
    return x<0?-1:x>0?1:0;
}

int mult(int id,int m){
    auto x=NAF(m);
    vector<int> add,sub;
    for(int i=0;i<x.size();i++){
        int s=sgn(m)*x[i];
        if(i)id=add_machine(id,id);
        if(s>0)add.emplace_back(id);
        if(s<0)sub.emplace_back(id);
    }
    int res=add.back();
    add.pop_back();
    for(auto i:add)res=add_machine(res,i);
    for(auto i:sub)res=minus_machine(res,i);
    return res;
}

int make_circuit(int n, int m, int p) {
    int g=__gcd(n,m);
    if(p%g)return -1;
    int x=1,y=2;
    if(n<m)swap(n,m),swap(x,y);
    while(m){
        ll q=n/m;
        n-=q*m;
        x=minus_machine(x,mult(y,q));
        swap(n,m),swap(x,y);
    }
    return mult(x,p/g);
}