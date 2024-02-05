#include<bits/stdc++.h>

using namespace std;

using ll = long long;

ll n,p;

ll binpow(ll a,ll b){
    ll res=1;
    while(b){
        if(b&1)res=res*a%p;
        a=a*a%p;
        b>>=1;
    }
    return res;
}

void runcase(){
    cin >> n >> p;
    // should have n%=p here
    cout << (n*binpow(n+1,n-1))%p << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}