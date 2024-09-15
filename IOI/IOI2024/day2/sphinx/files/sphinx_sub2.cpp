#include <bits/stdc++.h>
#include "sphinx.h"

using namespace std;

vector<int> find_colours(int N,vector<int> X,vector<int> Y){
    vector<int> ans(N);
    for(int i=0;i<N;i++){
        for(int j=1;j<N;j++){
            vector<int> tmp(N,j);
            tmp[i]=-1;
            if(perform_experiment(tmp)==1){
                ans[i]=j;
                break;
            }
        }
    }
    return ans;
}
