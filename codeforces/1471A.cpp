#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,k;
        cin >> n >> k;
        vector<int> a(n);
        ll sum=0,mx=0;
        for(auto &x:a){
            cin >> x;
            mx+=(x-1)/k+1;
            sum+=x;
        }
        cout << (sum-1)/k+1 << " " << mx << "\n";
    }
}