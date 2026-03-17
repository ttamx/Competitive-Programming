#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll a,b,c;
    cin >> a >> b >> c;
    ll base=0;
    if(a>=18){
        base+=a/9-1;
        a=9+a%9;
    }
    if(b>=18){
        base+=b/9-1;
        b=9+b%9;
    }
    if(c>=18){
        base+=c/9-1;
        c=9+c%9;
    }
    ll ans=0;
    for(ll e=0;e<=min({a,b,c});e++){
        ans=max(ans,e+(a-e)/3+(b-e)/3+(c-e)/3);
    }
    cout << base*3+ans << "\n";
}