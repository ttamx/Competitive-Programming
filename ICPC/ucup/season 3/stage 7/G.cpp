#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int mx=0;
    for(int i=0;i<n;i++){
        int mn=1e9;
        for(int i=0;i<n;i++){
            int x;
            cin >> x;
            mn=min(mn,x);
        }
        mx=max(mx,mn);
    }
    cout << mx;
}