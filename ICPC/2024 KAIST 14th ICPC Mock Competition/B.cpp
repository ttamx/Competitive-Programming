#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n;
    cin >> n;
    if(n<=5){
        cout << -1 << "\n";
    }else if(n%2==0){
        cout << 3 << "\n";
        cout << 1 << " " << n/2 << " " << n/2+1 << "\n";
    }else{
        cout << 4 << "\n";
        cout << 1 << " " << 3 << " " << n-3 << " " << n-2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        solve();
    }
}