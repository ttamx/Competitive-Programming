#include<bits/stdc++.h>

using namespace std;

int dp[10];

void runcase(){
    int n;
    cin >> n;
    int ans=0;
    while(n){
        int tmp=1;
        while(n/tmp>=10)tmp*=10;
        ans+=n/tmp;
        n=tmp-1;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    for(int i=2;i<10;i++)dp[i]=dp[i-1]+10;
    while(t--)runcase();
}