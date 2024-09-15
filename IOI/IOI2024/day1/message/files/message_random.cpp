#include <bits/stdc++.h>
#include "message.h"

using namespace std;

const int B=31;
const int S=19;

int sheet[]={1983195832,2101965561,1755637238,1065339280,1921786910,1272696727,1454432438,434617775,178359115,1074245070,2137531047,1815418164,1227813932,903951974,134338053,2139415691,1314611801,216938920,399056989,1284821116,9216263,814158913,2095632372,1228376885,1806889688,828987326,2059299402,1669259094,1440790300,1597715994};

void send_message(vector<bool> M,vector<bool> C){
    int s=M.size();
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(!C[i]){
            pos.emplace_back(i);
        }
    }
    for(int i=0;i<S;i++){
        vector<bool> tmp(B);
        for(int j=0;j<B;j++){
            if(!C[j]){
                tmp[j]=sheet[i]>>j&1;
            }
        }
        send_packet(tmp);
    }
    int rem=s%16;
    {
        vector<bool> tmp(B);
        for(int i=0;i<4;i++){
            tmp[pos[i]]=rem>>i&1;
        }
        send_packet(tmp);
    }
    int cur=0;
    while(cur<M.size()){
        vector<bool> tmp(B);
        for(auto x:pos){
            if(cur<s){
                tmp[x]=M[cur];
                cur++;
            }
        }
        send_packet(tmp);
    }
}

vector<bool> receive_message(vector<vector<bool>> R){
    int cur=0;
    vector<bool> C(B);
    for(int i=0;i<S;i++){
        for(int j=0;j<B;j++){
            if(R[cur][j]!=(sheet[i]>>j&1)){
                C[j]=true;
            }
        }
        cur++;
    }
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(!C[i]){
            pos.emplace_back(i);
        }
    }
    assert(pos.size()==16);
    int rem=0;
    for(int i=0;i<4;i++){
        if(R[cur][pos[i]]){
            rem|=1<<i;
        }
    }
    cur++;
    vector<bool> ans;
    for(;cur<R.size();cur++){
        for(auto i:pos){
            ans.emplace_back(R[cur][i]);
        }
    }
    if(rem>0){
        while(ans.size()%16!=rem){
            ans.pop_back();
        }
    }
    return ans;
}
