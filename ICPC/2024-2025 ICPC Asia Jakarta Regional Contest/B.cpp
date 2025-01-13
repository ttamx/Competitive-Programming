#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n,d,s;
    cin >> n >> d >> s;
    if(d<s){
        cout << s << "\n";
        exit(0);
    }
    n/=s,d/=s;
    ll lim=min(n,d*2);
    if(lim%2==0){
        cout << lim*s;
        exit(0);
    }
    for(ll i=1;i*i<=lim;i++){
        if(lim%i==0){
            if((i<=d&&lim-i<=d)||(lim/i<=d&&lim-lim/i<=d)){
                cout << lim*s;
                exit(0);
            }
        }
    }
    cout << (lim-1)*s;
    exit(0);
}