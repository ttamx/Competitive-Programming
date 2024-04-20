#include "immigration.h"
#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int ord[N],id[N];
int ans=1,cur=1;
stack<int> s[N];

int immigration(int n,vector<int> a){
    for(int i=0;i<n;i++)ord[a[i]]=i;
    for(auto x:a){
        for(;cur<=x;cur++){
            if(!s[ans].empty()&&ord[s[ans].top()]<ord[cur])ans++;
            s[ans].emplace(cur);
            id[cur]=ans;
        }
        s[id[x]].pop();
    }
    return ans;
}