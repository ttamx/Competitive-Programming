#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void solve(){
    string s;
    cin >> s;
    int n=s.size();
    ll ans=0;
    for(int i=1;i<=n;i++){
        ans+=1LL*i*(n-i+1);
    }
    for(int i=0;i<n;i++){
        if(s[i]=='0'){
            ans+=(n-i);
        }
    }
    for(int i=0;i+1<n;i++){
        if(s[i]==s[i+1]){
            ans+=1LL*(i+1)*(n-i-1);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}