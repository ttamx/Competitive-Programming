#include<bits/stdc++.h>

using namespace std;

int dp[1<<20];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int base=0;
    for(auto x:a)base^=x;
    vector<int> t(n,base);
    for(int v=1;v<(1<<20);v<<=1){
        if(base&v)continue;
        vector<int> pos;
        int last=-1;
        for(int i=0;i<n;i++){
            if(a[i]&v){
                if(last==-1){
                    last=i;
                }else{
                    for(int j=last;j<i;j++){
                        t[j]|=v;
                    }
                    last=-1;
                }
            }
        }
    }
    for(auto x:t){
        dp[x]++;
    }
    for(int j=1;j<(1<<20);j<<=1){
        for(int i=0;i<(1<<20);i++){
            if(i&j){
                dp[i]+=dp[i^j];
            }
        }
    }
    for(int i=1;i<(1<<20);i++){
        dp[i]=max(dp[i],dp[i-1]);
    }
    int p=0;
    for(int i=1;i<=n;i++){
        while(dp[p]<i)p++;
        cout << p << " \n"[i==n];
    }
}