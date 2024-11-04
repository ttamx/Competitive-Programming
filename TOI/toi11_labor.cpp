#include <bits/stdc++.h>
#include <stdio.h>
using namespace std;
#define ll long long int
ll ar[1000000];
ll N,M;
int check(ll mid) {
    ll a = 0;
    for (int i=0;i<M;i++) {
        a+=mid/ar[i];
    }
    if (a>=N) {
        return 1;
    } else {
        return 0;
    }
}
int main() {
    cin>>M>>N;
    for (int i=0;i<M;i++) {
        cin >> ar[i];
    }
    ll l = 0;
    ll r = 1e11;

    while (l<r) {
        ll mid = (l+r)/2;
        if (check(mid)) {
            r = mid;
        } else {
            l = mid+1;
        }
    }
    cout << l;

}