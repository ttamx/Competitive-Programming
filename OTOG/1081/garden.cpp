#include "garden.h"
#include <bits/stdc++.h>
using namespace std;

int findMinimumTime(int N,int M){
    vector<int> val(M);
    for(int i=0;i<M;i++){
        string s(M,'0');
        s[i]='1';
        val[i]=askInw(s);
    }
    vector<int> ord(M);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){return val[i]<val[j];});
    string s(M,'0');
    int cur=0;
    for(auto i:ord){
        s[i]='1';
        int tmp=askInw(s);
        if(tmp==cur+val[i]){
            cur+=val[i];
        }else{
            s[i]='0';
        }
    }
    return cur;
}