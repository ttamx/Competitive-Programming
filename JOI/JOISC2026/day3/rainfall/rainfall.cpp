#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int m,n,k;
    ll x1,y1,z1,x2,y2,z2;
    cin >> m >> n >> k;
    cin >> x1 >> y1 >> z1;
    cin >> x2 >> y2 >> z2;
    ll tot=z1*z1+z2*z2;
    ll x=max(x1,x2);
    ll y=max(y1,y2);
    ll z=min(x1+y1+z1,x2+y2+z2)-x-y;
    ll c=z*z;
    cout << tot-c << "\n";
    cout << c << "\n";
}