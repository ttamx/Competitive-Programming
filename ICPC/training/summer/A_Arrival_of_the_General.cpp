#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    int mx=0;
    for(int i=1;i<n;i++){
        if(a[i]>a[mx])mx=i;
    }
    int mn=n-1;
    for(int i=n-2;i>=0;i--){
        if(a[i]<a[mn])mn=i;
    }
    int ans=mx+n-1-mn;
    if(mx>mn)ans--;
    cout << ans << "\n";
}