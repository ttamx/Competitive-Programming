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
        for(auto &x:a)cin >> x;
        int ans=0;
        for(int i=0;i+1<n;i++){
            ans+=a[i]>a[i+1];
        }
        cout << ans << "\n";
    }
}