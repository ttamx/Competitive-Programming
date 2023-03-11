#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x >> x;
    int ans=0;
    for(int i=n-2;i>=0;i--){
        if(a[i]<=a[i+1]){
            a[i]=a[i+1];
            ans++;
        }
    }
    cout << ans;
}