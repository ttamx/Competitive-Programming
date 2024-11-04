#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=998244353;

void runcase(){
    ll w,g,l;
    cin >> w >> g >> l;
    ll v=(l*2+1)%MOD;
    ll d=(w-g)%MOD;
    cout << v*d%MOD << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}