#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    ll x;
    cin >> x;
    ll ans=1;
    int p=0;
    for(ll i=1;x>1;i<<=1){
        if(p)ans+=i;
        if(x%2==0){
            x/=2;
        }else{
            x-=x/2+p;
            p^=1;
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}