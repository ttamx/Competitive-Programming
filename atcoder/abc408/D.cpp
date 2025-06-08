#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        string s;
        cin >> s;
        vector<int> f(n+1);
        for(int i=0;i<n;i++){
            f[i+1]=f[i]+(s[i]=='1');
        }
        int mx=0,ans=2*n;
        for(int i=1;i<=n;i++){
            int v=i-2*f[i];
            mx=max(mx,v);
            ans=min(ans,v-mx);
        }
        cout << ans+f[n] << "\n";
    }
}