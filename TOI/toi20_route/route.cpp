#include <bits/stdc++.h>
#include "route.h"

using namespace std;

vector<pair<int,int>> route(int n,vector<int> w){
    int m=w.size();
    vector<pair<int,int>> ans(m);
    int cur=1,aux=2,cnt=m-n+1;
    for(int i=0;i<m;i++){
        if(cnt>0&&aux<cur){
            ans[i]={aux++,cur};
            cnt--;
        }else{
            ans[i]={1,++cur};
            aux=2;
        }
    }
    return ans;
}