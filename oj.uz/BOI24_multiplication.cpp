#include<bits/stdc++.h>

using namespace std;

const int MOD=1e9+7;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int ans=1;
    while(n--){
        long long x;
        cin >> x;
        ans=x%MOD*ans%MOD;
    }
    cout << ans;
}