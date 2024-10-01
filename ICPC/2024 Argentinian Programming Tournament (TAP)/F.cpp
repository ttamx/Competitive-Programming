#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int ans=0;
    for(auto x:a){
        if(x)ans++;
        else ans--;
    }
    for(int i=2;i<n;i++){
        if(a[i]+a[i-1]+a[i-2]==3){
            ans++;
        }
    }
    cout << ans;
}