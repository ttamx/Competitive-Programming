#include<bits/stdc++.h>

using namespace std;

const int N=512;

int q,idx=1;
long long ans[N],pw[10];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    vector<vector<long long>> s(10);
    for(int i=1;i<=9;++i){
        ans[idx++]=i;
        s[i].emplace_back(i);
    }
    pw[0]=1;
    for(int d=1;d<=9;++d){
        pw[d]=pw[d-1]*10;
        vector<vector<long long>> tmp(10);
        for(int i=1;i<=9;++i){
            for(int j=i+1;j<=9;++j){
                for(auto k:s[j]){
                    ans[idx]=i*pw[d]+k;
                    tmp[i].emplace_back(ans[idx]);
                    idx++;
                }
            }
        }
        s=tmp;
    }
    cin >> q;
    while(q--){
        long long x;
        cin >> x;
        if(x>=512)cout << -1 << '\n';
        else cout << ans[x] << '\n';
    }
}