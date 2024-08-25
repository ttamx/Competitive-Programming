#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int m=1<<n;
    vector<int> a(m);
    for(auto &x:a)cin >> x;
    sort(a.rbegin(),a.rend());
    long long ans=-1e9;
    long long sum=0;
    for(int i=1;i<=m;i++){
        sum+=a[i-1];
        if(i==(i&-i)){
            ans=max(ans,sum);
        }
    }
    cout << ans << "\n";
}