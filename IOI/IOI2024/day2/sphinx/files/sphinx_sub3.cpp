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
    int cnt=0;
    for(int col=0;col<n;col++){
        for(int t=0;t<2;t++){
            vector<int> pos;
            vector<int> filter(n,col);
            for(int i=t;i<n;i+=2){
                pos.emplace_back(i);
                filter[i]=-1;
            }
            for(int i=0;i<pos.size();i++){
                assert(++cnt<=2750);
                if(perform_experiment(filter)==n){
                    break;
                }
                int l=i,r=pos.size()-1;
                while(l<r){
                    int m=(l+r)/2;
                    vector<int> tmp(n,col);
                    for(int j=0;j<pos.size();j++){
                        if(j<i){
                            tmp[pos[j]]=n;
                        }else if(j>m){
                            tmp[pos[j]]=n;
                        }else{
                            tmp[pos[j]]=-1;
                        }
                    }
                    assert(++cnt<=2750);
                    if(perform_experiment(tmp)!=n){
                        r=m;
                    }else{
                        l=m+1;
                    }
                }
                ans[pos[l]]=col;
                for(int j=i;j<=l;j++){
                    filter[pos[j]]=n;
                }
                i=l;
            }
        }
    }
    return ans;
}
