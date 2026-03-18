#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto pre=a,suf=a;
    for(int i=1;i<n;i++){
        pre[i]=gcd(pre[i-1],a[i]);
    }
    for(int i=n-2;i>=0;i--){
        suf[i]=gcd(suf[i+1],a[i]);
    }
    long long ans=0;
    for(int i=0;i<n-1;i++){
        ans+=min(pre[i],suf[i]);
    }
    cout << ans << "\n";
}