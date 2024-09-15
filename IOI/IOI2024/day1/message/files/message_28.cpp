#include <bits/stdc++.h>
#include "message.h"

using namespace std;

const int B=31;
const int S=29;

int dp[B+1][B+1];



void init(){
    dp[0][0]=1;
    for(int i=1;i<=B;i++){
        for(int j=0;j<B;j++){
            dp[i][j]=dp[i-1][j];
        }
        for(int j=1;j<B;j++){
            dp[i][j]+=dp[i-1][j-1];
        }
    }
    cerr << dp[B][15] << "\n";
}

void send_message(vector<bool> M,vector<bool> C){
    init();
    int s=M.size();
    int res=0,cnt=15;
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(C[i]){
            res+=dp[B-i-1][cnt];
            cnt--;
        }else{
            pos.emplace_back(i);
        }
    }
    for(int i=0;i<S;i++){
        send_packet(vector<bool>(31,res>>i&1));
    }
    int rem=s%16;
    for(int i=0;i<4;i++){
        send_packet(vector<bool>(31,rem>>i&1));
    }
    int cur=0;
    while(cur<M.size()){
        vector<bool> tmp(31);
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
    init();
    int res=0,cnt=15;
    int cur=0;
    for(int i=0;i<S;i++){
        int sum=0;
        for(auto x:R[cur]){
            sum+=x;
        }
        if(sum>=16){
            res|=1<<i;
        }
        cur++;
    }
    int rem=0;
    for(int i=0;i<4;i++){
        int sum=0;
        for(auto x:R[cur]){
            sum+=x;
        }
        if(sum>=16){
            rem|=1<<i;
        }
        cur++;
    }
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(res>=dp[B-i-1][cnt]){
            res-=dp[B-i-1][cnt];
            cnt--;
        }else{
            pos.emplace_back(i);
        }
    }
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
