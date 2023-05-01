#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int a,b,c,q;
bool dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> a >> b >> c >> q;
    for(int i=1;i<N;i++){
        dp[i]=!dp[i-1];
        if(i>=a)dp[i]|=!dp[i-a];
        if(i>=b)dp[i]|=!dp[i-b];
        if(i>=c)dp[i]|=!dp[i-c];
    }
    while(q--){
        int n;
        cin >> n;
        cout << (dp[n]?"gorn":"lang") << "\n";
    }
}