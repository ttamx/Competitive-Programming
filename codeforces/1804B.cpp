#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k,d,w;
    cin >> n >> k >> d >> w;
    vector<int> t(n);
    for(auto &x:t)cin >> x;
    int idx=0,ans=0;
    while(idx<n){
        int cnt=0;
        int r=t[idx]+d+w;
        ans++;
        while(idx<n&&t[idx]<=r&&cnt<k){
            cnt++;
            idx++;
        }
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}