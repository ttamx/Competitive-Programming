#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        vector<int> cnt(n+1);
        for(auto &x:a){
            cin >> x;
            cnt[x]++;
        }
        vector<int> cnt2(n+1);
        for(int i=1;i<=n;i++){
            for(int j=i*2;j<=n;j+=i){
                cnt2[j]+=cnt[i];
                cnt2[i]+=cnt[j];
            }
        }
        int ans=n;
        for(int i=1;i<=n;i++){
            ans=min(ans,(n-cnt[i]-cnt2[i])*2+cnt2[i]);
        }
        cout << ans << "\n";
    }
}