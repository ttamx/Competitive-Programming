#include "tnt.h"
#include<bits/stdc++.h>

using namespace std;

typedef pair<int,int> p2;

const int inf=1e9;

vector<int>find_truck(int n){
    vector<p2> ans;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)ans.emplace_back(i,j);
    auto calc=[&](p2 x,int ct){
        return (x.first+x.second*ct)%n;
    };
    int t=1;
    if(n==(n&-n)){
        int b=0,c=1;
        while((c<<2)<n)c<<=2;
        while(ans.size()>4){
            if(!b)b=c;
            vector<int> res;
            for(int i=0;i<n;i++)if(i&b)res.emplace_back(i);
            vector<bool> ask(n);
            for(auto x:res)ask[x]=true;
            vector<p2> ans2;
            bool tmp=find_tnt(res);
            for(auto x:ans)if(!ask[calc(x,t)]^tmp)ans2.emplace_back(x);
            swap(ans,ans2);
            t++;
            b>>=1;
        }
    }
    while(ans.size()>4){
        vector<int> cnt(n);
        for(auto x:ans)cnt[calc(x,t)]++;
        int sz=ans.size();
        int sum=0;
        vector<int> p(n);
        p2 best(inf,-1);
        int tar=ans.size()/2;
        for(int l=0,r=0;l<n;l++){
            while(sum+cnt[r%n]<=tar)sum+=cnt[(r++)%n];
            p[l]=r-1;
            best=min(best,p2(tar-sum,l));
            sum-=cnt[l];
        }
        int id=best.second;
        vector<int> res;
        for(int i=id;i<=p[id];i++)res.emplace_back(i%n);
        vector<bool> ask(n);
        for(auto x:res)ask[x]=true;
        vector<p2> ans2;
        bool tmp=find_tnt(res);
        for(auto x:ans)if(!ask[calc(x,t)]^tmp)ans2.emplace_back(x);
        swap(ans,ans2);
        t++;
    }
    while(ans.size()>1){
        vector<int> res;
        if(ans.size()==4){
            auto get=[&](){
                for(int i=0;i<4;i++)for(int j=0;j<i;j++){
                    if(calc(ans[i],t)==calc(ans[j],t)){
                        return vector<int>(1,calc(ans[i],t));
                    }
                }
                for(int i=0;i<4;i++)for(int j=0;j<i;j++){
                    vector<int> res;
                    for(int k=0;k<4;k++)if(i!=k&&j!=k)res.emplace_back(k);
                    if(calc(ans[i],t+1)==calc(ans[j],t+1))continue;
                    if(calc(ans[res[0]],t+1)==calc(ans[res[1]],t+1))continue;
                    for(auto &x:res)x=calc(ans[x],t);
                    return res;
                }
                return vector<int>(0);
            };
            res=get();
        }else if(ans.size()==3){
            auto get=[&](){
                for(int i=0;i<3;i++)for(int j=0;j<i;j++){
                    if(calc(ans[i],t)==calc(ans[j],t)){
                        return vector<int>(1,calc(ans[i],t));
                    }
                }
                vector<int> res={0,1};
                for(auto &x:res)x=calc(ans[x],t);
                return res;
            };
            res=get();
        }else{
            res={calc(ans[0],t)};
        }
        vector<bool> ask(n);
        for(auto x:res)ask[x]=true;
        vector<p2> ans2;
        bool tmp=find_tnt(res);
        for(auto x:ans)if(!ask[calc(x,t)]^tmp)ans2.emplace_back(x);
        swap(ans,ans2);
        t++;
    }
    return {ans[0].first,ans[0].second};
}