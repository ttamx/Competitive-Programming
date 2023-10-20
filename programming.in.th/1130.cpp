#include<bits/stdc++.h>

using namespace std;

const int mod=49999;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    long long ans=0;
    for(int i=1;i<=n;i++){
        long long x;
        cin >> x;
        ans+=x*(i-1-n+i),ans%=mod;
    }
    for(int i=1;i<=n-2;i++)ans*=i,ans%=mod;
    cout << ans;
}