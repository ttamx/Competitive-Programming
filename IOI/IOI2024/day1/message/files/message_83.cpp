#include <bits/stdc++.h>
#include "message.h"

using namespace std;

const int B=31;
const int S=28;
const int N=4;

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
}

void send_message(vector<bool> M,vector<bool> C){
    init();
    int tail=M.back()^1;
    M.emplace_back(tail);
    int res=0,cnt=15;
    vector<int> pos;
    for(int i=0;i<B;i++){
        if(!C[i]){
            pos.emplace_back(i);
        }
    }
    int num=30;
    for(int i=0;i<B;i++){
        if(i==pos[0]){
            continue;
        }
        num--;
        if(C[i]){
            res+=dp[num][cnt];
            cnt--;
        }
    }
    for(int i=0;i<4;i++){
        send_packet(vector<bool>(B,pos[0]>>i&1));
    }
    int cur=0;
    for(int i=0;i<S;i++){
        vector<bool> tmp(B);
        tmp[pos[0]]=res>>i&1;
        for(int j=1;j<16;j++){
            if(cur<M.size()){
                tmp[pos[j]]=M[cur];
                cur++;
            }else{
                tmp[pos[j]]=tail;
            }
        }
        send_packet(tmp);
    }
    while(cur<M.size()){
        vector<bool> tmp(B);
        for(auto x:pos){
            if(cur<M.size()){
                tmp[x]=M[cur];
                cur++;
            }else{
                tmp[x]=tail;
            }
        }
        send_packet(tmp);
    }
}

vector<bool> receive_message(vector<vector<bool>> R){
    init();
    int res=0,cnt=15;
    int head=0;
    for(int i=0;i<4;i++){
        int cnt=0;
        for(auto x:R[i]){
            cnt+=x;
        }
        if(cnt>=16){
            head|=1<<i;
        }
    }
    for(int i=0;i<S;i++){
        if(R[i+4][head]){
            res|=1<<i;
        }
    }
    vector<int> pos{head};
    int num=30;
    for(int i=0;i<B;i++){
        if(i==head){
            continue;
        }
        num--;
        if(res>=dp[num][cnt]){
            res-=dp[num][cnt];
            cnt--;
        }else{
            pos.emplace_back(i);
        }
    }
    vector<bool> ans;
    for(int i=0;i<S;i++){
        for(int j=1;j<16;j++){
            ans.emplace_back(R[i+4][pos[j]]);
        }
    }
    for(int cur=S+4;cur<R.size();cur++){
        for(auto i:pos){
            ans.emplace_back(R[cur][i]);
        }
    }
    int tail=ans.back();
    while(ans.back()==tail){
        ans.pop_back();
    }
    return ans;
}
