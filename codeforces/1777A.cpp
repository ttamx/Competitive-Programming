#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int idx=1,ans=0;
    while(idx<n){
        while(idx<n&&a[idx]%2==a[idx-1]%2){
            idx++;
            ans++;
        }
        idx++;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}