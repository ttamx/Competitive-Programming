#include "moodeng.h"
#include <bits/stdc++.h>

using namespace std;

void search(int n,int m,int T){
    mt19937 rng(998244353);
    int l1=0,r1=n-1,l2=0,r2=m-1;
    vector<vector<bool>> a(n,vector<bool>(m,false));
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            a[i][j]=(i+j)%2;
        }
    }
    int parity=query(a);
    auto expand=[&](){
        l1=max(l1-1,0);
        r1=min(r1+1,n-1);
        l2=max(l2-1,0);
        r2=min(r2+1,m-1);
        parity^=1;
    };
    expand();
    auto ask=[&](int l1,int r1,int l2,int r2){
        vector<vector<bool>> a(n,vector<bool>(m,false));
        for(int i=l1;i<=r1;i++){
            for(int j=l2;j<=r2;j++){
                a[i][j]=true;
            }
        }
        return query(a);
    };
    auto ask2=[&](int i,int j){
        vector<vector<bool>> a(n,vector<bool>(m,false));
        a[i][j]=true;
        return query(a);
    };
    auto work=[&](){
        if(r1-l1>r2-l2){
            int mid=(l1+r1)/2;
            if(ask(l1,mid,l2,r2))r1=mid;
            else l1=mid+1;
        }else{
            int mid=(l2+r2)/2;
            if(ask(l1,r1,l2,mid))r2=mid;
            else l2=mid+1;
        }
        expand();
    };
    auto calc=[&](){
        vector<pair<int,int>> res;
        for(int i=l1;i<=r1;i++){
            for(int j=l2;j<=r2;j++){
                if((i==l1||i==r1)&&(j==l2||j==r2)){
                    if(i>0&&i<n-1&&j>0&&j<m-1){
                        continue;
                    }
                }
                if((i+j)%2==parity){
                    res.emplace_back(i,j);
                }
            }
        }
        return res;
    };
    while(true){
        auto cand=calc();
        if(cand.size()>24){
            work();
        }else{
            auto [x,y]=cand[rng()%((int)cand.size())];
            if(ask2(x,y))return;
            expand();
        }
    }
}