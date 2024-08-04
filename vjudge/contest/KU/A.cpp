#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d;
    cin >> n >> d;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    int ans=0;
    for(int i=0;i<n;i++){
        int j=i;
        while(j<n&&a[j+1]-a[i]<=d)j++;
        ans++;
        i=j;
    }
    cout << ans << "\n";
}