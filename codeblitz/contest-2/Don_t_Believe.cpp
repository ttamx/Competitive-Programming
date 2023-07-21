#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

typedef long long ll;


int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int q;
    ll n;
    cin >> n >> q;
    while(q--){
        ll x,y;
        cin >> x >> y;
        ll p=x+y+1;
        cout << (n+((n*(n+1)*(n+2)/6)%p*(x+y)%p)+((n*(n+1)/2)%p))%p << "\n";
    }
}