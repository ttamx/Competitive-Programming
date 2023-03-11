#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> s(n);
    int mn=2e9;
    for(auto &x:s)cin >> x,mn=min(mn,x);
    ll dist=1ll*mn*k;
    int cnt=1;
    for(int i=1;i<n;i++){
        if((dist-1)/s[i]+1>=k)cnt++;
        else break;
    }
    cout << cnt;
}