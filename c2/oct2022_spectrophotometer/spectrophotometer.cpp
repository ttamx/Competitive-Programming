#include "spectrophotometer.h"
#include<bits/stdc++.h>

using namespace std;

void sort_lasers(int N) {
    vector<int> h(3,-1);
    for(int i=0;i<3*N;i++){
        int j=2,c=i;
        while(j>0){
            if(h[j]==-1){
                h[j]=c;
                break;
            }
            if(call_swap(h[j],c))break;
            c=h[j--]++;
        }
    }
}