#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,n;
    cin >> m >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int ans=INT_MAX;
    for(int i=m-1;i<n;i++){
        ans=min(ans,a[i]-a[i-m+1]);
    }
    cout << ans << "\n";
}