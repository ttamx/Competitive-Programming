#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> a(n),b(n),c(n),d(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    for(auto &x:c)cin >> x;
    for(auto &x:d)cin >> x;
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(c.begin(),c.end());
    sort(d.begin(),d.end());
    int ans=2e9;
    for(int i=0;i<=k;i++){
        if(i>n||k-i>n)continue;
        int res=0;
        for(int j=0;j<i;j++)res=max(res,a[j]+c[i-j-1]);
        for(int j=0;j<k-i;j++)res=max(res,b[j]+d[k-i-j-1]);
        ans=min(ans,res);
    }
    cout << ans;
}