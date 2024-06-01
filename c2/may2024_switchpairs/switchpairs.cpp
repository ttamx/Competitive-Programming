#include"switchpairs.h"
#include<bits/stdc++.h>

using namespace std;

int n;
int door;
vector<int> pos,state;

bool ask(){
    return control_switches(state)>door;
}

void answer(int a,int b,int x,int y){
    state[a]=x,state[b]=y;
    pos.erase(lower_bound(pos.begin(),pos.end(),a));
    pos.erase(lower_bound(pos.begin(),pos.end(),b));
}

int find_first(int t,vector<int> a){
    int l=0,r=a.size()-1;
    while(l<r){
        int m=(l+r)/2;
        for(int i=0;i<a.size();i++)state[a[i]]=t^(i>m);
        if(ask())r=m;
        else l=m+1;
    }
    return l;
}

int find_last(int t,vector<int> a){
    int l=-1,r=a.size()-2;
    while(l<r){
        int m=(l+r+1)/2;
        for(int i=0;i<a.size();i++)state[a[i]]=t^(i>m);
        if(ask())l=m;
        else r=m-1;
    }
    return l;
}

bool solve_same(int t){
    for(auto x:pos)state[x]=t;
    if(!ask())return false;
    answer(pos[find_last(t^1,pos)+1],pos[find_first(t,pos)],t,t);
    return true;
}

void solve(int _n){
    n=_n;
    state.assign(2*n,0);
    pos.resize(2*n);
    iota(pos.begin(),pos.end(),0);
    for(int i=0;i<n;i++){
        door=i;
        if(solve_same(0))continue;
        if(solve_same(1))continue;
        for(int k=0;(1<<k)<pos.size();k++){
            vector<int> a[2];
            for(int i=0;i<pos.size();i++)a[i>>k&1].emplace_back(pos[i]);
            for(int i=0;i<2;i++)for(auto x:a[i])state[x]=i;
            if(!ask()){
                swap(a[0],a[1]);
                for(int i=0;i<2;i++)for(auto x:a[i])state[x]=i;
                if(!ask())continue;
            }
            for(auto x:a[1])state[x]=1;
            int tmp=a[0][find_first(0,a[0])];
            for(auto x:a[0])state[x]=0;
            answer(tmp,a[1][find_first(1,a[1])],0,1);
            break;
        }
    }
    ask();
}
