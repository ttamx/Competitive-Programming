#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        ll a,b,c,d;
        cin >> a >> b >> c >> d;
        ll x=abs(a-c);
        ll y=abs(b-d);
        if(x<y)swap(x,y);
        ll ans=x+y;
        ans+=(x-y)/2*2;
        cout << ans << "\n";
    }
}