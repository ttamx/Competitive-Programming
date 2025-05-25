#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=100005;

int n,k;
ll sum;
multiset<int>  msl,msr;

void insert(ll v){
    msl.emplace(v);
    sum+=v;
    if(msl.size()>k){
        auto it=prev(msl.end());
        sum-=*it;
        msr.emplace(*it);
        msl.erase(it);
    }
}

void erase(ll v){
    if(msr.empty()||v<*msr.begin()){
        sum-=x;
        msl.erase(*msl).begin();
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
}