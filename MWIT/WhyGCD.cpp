#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    cin >> q;
    while(q--){
        long long a,b;
        cin >> a >> b;
        cout << a*b/gcd(a,b) << '\n';
    }
}