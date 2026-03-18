#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll h,r;
    cin >> r >> h;
    ll ans=h/r*2;
    h%=r;
    if(h*h*4>=r*r*3)ans+=3;
    else if(h*2>=r)ans+=2;
    else ans++;
    cout << ans << "\n";
}