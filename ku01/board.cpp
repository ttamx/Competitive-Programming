#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,s;
    cin >> n >> m >> s;
    vector<vector<int>> a(n);
    for(auto &v:a)v.resize(m);
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cin >> a[i][j],a[i][j]+=i*s;
    int ans=0;
    for(int i=0;i<m;i++){
        int mx=0;
        for(int j=0;j<n;j++)if(a[j][i]>mx)mx=a[j][i],ans++;
    }
    cout << ans;
}