#include <bits/stdc++.h>
#include "message.h"

using namespace std;

void send_message(vector<bool> M, vector<bool> C){
    for(auto x:M){
        send_packet(vector<bool>(31,x));
    }
}

vector<bool> receive_message(vector<vector<bool>> R){
    vector<bool> ans;
    for(auto x:R){
        int cnt=0;
        for(auto b:x){
            cnt+=b;
        }
        ans.emplace_back(cnt>=16);
    }
    return ans;
}
