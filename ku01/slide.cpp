#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=0;
    for(int i=0;i<n;i++)for(int j=i+1;j<n;j++)if(a[j]>a[i])ans++;
    cout << ans;
}