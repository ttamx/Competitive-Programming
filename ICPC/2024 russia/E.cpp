#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    ll m;
    cin >> n >> m;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    long double tot=0;
    sort(a.rbegin(),a.rend());
    for(ll i=0;i<n;i++){
        m-=a[i]/(i+1);
        ll rem=a[i]%(i+1);
        if(rem>0){
            tot+=(long double)(a[i]%(i+1))/(i+1);
        }
    }
    if(tot-m>=-1e-9){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}