#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

const int M=5e6+5;

int lp[M],phi[M];
vector<int> prime;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    phi[1]=1;
    for(int i=2;i<M;i++){
        if(lp[i]==0){
            lp[i]=i;
            phi[i]=i-1;
            prime.emplace_back(i);
        }else{
            if(lp[i]==lp[i/lp[i]]){
                phi[i]=phi[i/lp[i]]*lp[i];
            }else{
                phi[i]=phi[i/lp[i]]*(lp[i]-1);
            }
        }
        for(auto p:prime){
            if(p>lp[i]||i*p>=M)break;
            lp[i*p]=p;
        }
    }
}