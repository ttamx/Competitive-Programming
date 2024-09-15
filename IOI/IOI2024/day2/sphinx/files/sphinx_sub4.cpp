#include <bits/stdc++.h>
#include "sphinx.h"

using namespace std;

vector<int> find_colours(int n,vector<int> X,vector<int> Y){
    int m=X.size();
    vector<int> ans(n);
    if(n<=50){
        for(int i=0;i<n;i++){
            for(int j=1;j<n;j++){
                vector<int> tmp(n,j);
                tmp[i]=-1;
                if(perform_experiment(tmp)==1){
                    ans[i]=j;
                    break;
                }
            }
        }
        return ans;
    }
    if(m==n*(n-1)/2){
        for(int i=0;i<n;i++){
            int l=0,r=n-1;
            while(l<r){
                int m=(l+r)/2;
                vector<int> tmp(n,0);
                int col=0;
                for(int j=0;j<n;j++){
                    if(i==j)continue;
                    tmp[j]=col;
                    if(col<m)col++;
                }
                tmp[i]=-1;
                if(perform_experiment(tmp)==m+1)r=m;
                else l=m+1;
            }
            ans[i]=l;
        }
        return ans;
    }
    vector<int> p(n);
    iota(p.begin(),p.end(),0);
    function<int(int)> fp=[&](int u){
        return p[u]=(u==p[u]?u:fp(p[u]));
    };
    auto uni=[&](int u,int v){
        u=fp(u),v=fp(v);
        if(u!=v)p[u]=v;
    };
    for(int i=0;i<m;i++){
        int u=X[i],v=Y[i];
        if(u>v){
            swap(u,v);
        }
        vector<int> tmp(n,n);
        int base=((u==0||v==n-1)?2:3);
        tmp[u]=tmp[v]=-1;
        if(perform_experiment(tmp)==base){
            uni(u,v);
        }
    }
    for(int i=0;i<n;i++){
        ans[i]=fp(i);
    }
    return ans;
}
