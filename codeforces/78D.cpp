#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    cin >> n;
    if(n<=2){
        cout << 1 << "\n";
        exit(0);
    }
    auto check=[&](ll x,ll y){
        return (3*(2*x+y-1)*(2*x+y-1)+((y*3)+1)*((y*3)+1))<=4*n*n;
    };
    ll x=0;
    ll ans=0;
    for(ll y=0;;y++){
        while(check(x+1,y))x++;
        while(x>=0&&!check(x,y))x--;
        if(x<=0)break;
        ans+=x-1;
    }
    cout << ans*6+1 << "\n";
}