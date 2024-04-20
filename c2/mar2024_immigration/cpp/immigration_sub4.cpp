#include "immigration.h"
#include <bits/stdc++.h>

using namespace std;

const int N=5e5+5;

bool ok[N];

int immigration(int n,vector<int> a){
    set<int> s;
    int ans=0;
    for(auto x:a){
        ok[x]=true;
        if(!ok[x+1])ans++;
    }
    return ans;
}