#include "Anna.h"
#include <bits/stdc++.h>

using namespace std;

void Anna(int n){
    int c[2]={};
    int v=DrawCard(-1);
    for(int i=0;i<n;i++){
        int x=-1;
        if(i==0||c[v]<c[v^1]){
            x=0;
        }
        c[v]++;
        v=DrawCard(x);
    }
}