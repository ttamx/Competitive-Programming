#include "updown.h"
#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int sz[2*N],p[2*N];
map<long long,int> mp;

int fp(int u){
    if(u==p[u])return u;
    return p[u]=fp(p[u]);
}

vector<int> updown(int n, int m, vector<int> U, vector<int> V) {
    for(int i=0;i<2*n;i++)p[i]=i;
	for(int i=0;i<m;i++){
        int u=U[i],v=V[i];
        if(u>v)swap(u,v);
        u+=n;
        u=fp(u),v=fp(v);
        if(u==v)continue;
        p[u]=v;
	}
    for(int i=0;i<2*n;i++)sz[fp(i)]++;
    vector<int> ans(n);
    for(int i=0;i<n;i++){
        int x=p[i],y=p[i+n];
        if(x==y){
            sz[x]--;
        }else{
            if(x>y)swap(x,y);
            mp[x*2000000000ll+y]++;
        }
    }
    for(int i=0;i<n;i++){
        int x=p[i],y=p[i+n];
        if(x==y){
            ans[i]=sz[x]-1;
        }else{
            if(x>y)swap(x,y);
            ans[i]=sz[x]+sz[y]-mp[x*2000000000ll+y]-1;
        }
    }
    return ans;
}