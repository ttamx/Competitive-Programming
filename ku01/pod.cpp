#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> cnt(k);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        cnt[x-1]++;
    }
    int mn=2e9;
    for(auto x:cnt)mn=min(mn,x);
    cout << n-(mn*k);
}