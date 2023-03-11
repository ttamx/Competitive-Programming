#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    long long ans=0;
    for(int i=0;i<n-2*k;i++)ans+=a[i];
    for(int i=n-2*k;i<n-k;i++)ans+=a[i]/a[i+k];
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}