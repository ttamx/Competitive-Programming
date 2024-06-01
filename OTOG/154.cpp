#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n,q;
        cin >> n >> q;
        vector<long long> a(n);
        for(auto &x:a)cin >> x;
        for(int i=1;i<n;i++)a[i]+=a[i-1];
        while(q--){
            int l,r;
            cin >> l >> r;
            cout << a[r]-(l?a[l-1]:0LL) << "\n";
        }
    }
}