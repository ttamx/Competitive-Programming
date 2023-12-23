#include "longesttrip.h"
#include<bits/stdc++.h>

using namespace std;

int bsearch(vector<int> vec,vector<int> fixed){
    int l=0,r=vec.size()-1;
    while(l<r){
        int m=(l+r)/2;
        vector<int> res;
        for(int i=l;i<=m;i++)res.emplace_back(vec[i]);
        if(are_connected(res,fixed))r=m;
        else l=m+1;
    }
    return l;
}

vector<int> longest_trip(int N, int D){
    vector<int> path[2];
    for(int i=0;i<2;i++)path[i].emplace_back(i);
    bool ok=true;
    for(int i=2;i<N;i++){
        if(are_connected({i},{path[0].back()})){
            path[0].emplace_back(i);
            ok=true;
            continue;
        }
        if(!ok||are_connected({i},{path[1].back()})){
            path[1].emplace_back(i);
            ok=false;
            continue;
        }
        while(!path[1].empty()){
            path[0].emplace_back(path[1].back());
            path[1].pop_back();
        }
        ok=true;
        path[1].emplace_back(i);
    }
    if(path[0].size()<path[1].size())swap(path[0],path[1]);
    if(!are_connected(path[0],path[1]))return path[0];
    if(are_connected({path[0][0]},{path[1][0]})){
        reverse(path[1].begin(),path[1].end());
        auto ans=path[1];
        for(auto x:path[0])ans.emplace_back(x);
        return ans;
    }
    if(are_connected({path[0][0]},{path[1].back()})){
        auto ans=path[1];
        for(auto x:path[0])ans.emplace_back(x);
        return ans;
    }
    if(are_connected({path[0].back()},{path[1][0]})){
        auto ans=path[0];
        for(auto x:path[1])ans.emplace_back(x);
        return ans;
    }
    if(are_connected({path[0].back()},{path[1].back()})){
        auto ans=path[0];
        reverse(path[1].begin(),path[1].end());
        for(auto x:path[1])ans.emplace_back(x);
        return ans;
    }
    int id0=bsearch(path[0],path[1]);
    int id1=bsearch(path[1],{path[0][id0]});
    vector<int> ans;
    for(int i=0;i<path[0].size();i++)ans.emplace_back(path[0][(id0+i+1)%path[0].size()]);
    for(int i=0;i<path[1].size();i++)ans.emplace_back(path[1][(id1+i)%path[1].size()]);
    return ans;
}