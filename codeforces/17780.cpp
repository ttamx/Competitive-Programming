#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    int sum=0;
    for(auto &x:a)cin >> x,sum+=x;
    int ans=-2e9;
    for(int i=1;i<n;i++)ans=max(ans,sum-2*(a[i]+a[i-1]));
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}