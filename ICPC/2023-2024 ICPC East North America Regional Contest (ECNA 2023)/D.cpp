#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll s=0;
    for(int i=0;i<5;i++){
        ll a,b;
        cin >> a>> b;
        s+=a*b;
    }
    ll n,k;
    cin >> n >> k;
    cout << s/5*n/k << "\n";
}