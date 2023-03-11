#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int>cnt(300);
    int ans=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        ans=max(ans,++cnt[x-1]);
    }
    cout << ans;
}