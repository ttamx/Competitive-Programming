#include "molecules.h"
#include<bits/stdc++.h>

using namespace std;

vector<int> find_subset(int l,int u,vector<int> w){
    int n=w.size();
    vector<pair<int,int>> vec;
    for(int i=0;i<n;i++)vec.emplace_back(w[i],i);
    sort(vec.begin(),vec.end());
    int idx=0;
    long long sum=0;
    for(int i=0;i<n;i++){
        sum+=vec[i].first;
        while(sum>u)sum-=vec[idx++].first;
        if(l<=sum&&sum<=u){
            vector<int> ans;
            while(idx<=i)ans.emplace_back(vec[idx++].second);
            return ans;
        }
    }
    return vector<int>(0);
}