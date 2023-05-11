#include<bits/stdc++.h>

using namespace std;

multiset<int> ms;

bool usePakpim(int x){
    bool res=(ms.find(x)!=ms.end());
    ms.emplace(x);
    return res;
}

int usePeteza(){
    if(ms.empty())return INT_MAX;
    int res=*ms.rbegin();
    ms.erase(prev(ms.end()));
    return res;
}

int useBlackslex(){
    if(ms.empty())return INT_MIN;
    int res=*ms.begin();
    ms.erase(ms.begin());
    return res;
}