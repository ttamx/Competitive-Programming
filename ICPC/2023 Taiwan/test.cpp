#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=1e9+7;

void runcase(ll n){
    if(n<9){
        cout << n << "\n";
    }else if(n%2==0){
        cout << (n/2)%MOD << "\n";
    }else if(n==11){
        cout << 4 << "\n";
    }else if(n<18){
        cout << n-9 << "\n";
    }else{
        cout << max((n-9)/2, (ll)9)%MOD << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for (int i=1; i<=50; i++) if (i!=9) cout<<i<<' ', runcase(i);
}