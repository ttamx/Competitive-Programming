#include "tnt.h"
#include<bits/stdc++.h>

using namespace std;

vector<int>find_truck(int N){
    auto shift=[&](vector<int> &a,int b){
        for(auto &x:a)x=(x+b)%N;
    };
    int B=0,pos=0;
    for(int b=1;b<N;b*=1){
        vector<int> tmp;
        for(int i=0;i<N;i+=2*b)tmp.emplace_back(i);
        if(!find_tnt(tmp)){
            tmp.clear();
            for(int i=1;i<N;i+=2*b)tmp.emplace_back(i);
        }
        shift(tmp,b);
    }
}