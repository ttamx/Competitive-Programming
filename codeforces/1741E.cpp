#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<bool> dp(n+1,false);
    dp[0]=true;
    for(int i=1;i<=n;++i){
        int x;
        cin >> x;
        if(dp[i-1]&&i+x<=n)dp[i+x]=true;
        if(i-x-1>=0&&dp[i-x-1])dp[i]=true;
    }
    cout << (dp[n]?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}