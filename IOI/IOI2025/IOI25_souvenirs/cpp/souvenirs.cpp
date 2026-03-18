#include "souvenirs.h"
#include <bits/stdc++.h>

using namespace std;

using ll = long long;

void buy_souvenirs(int n, ll p0) {
    vector<ll> p(n);
    p[0]=p0;
    for(ll l=0,r=1;l<p0;l=r,r*=2){
        auto [pos,rem]=transaction(r);
        
    }
    return;
}
