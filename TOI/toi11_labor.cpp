#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const ll M=1e6+5;

ll n,m;
ll t[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> m >> n;
    for(int i=1;i<=m;i++)cin >> t[i];
    ll l=1,r=1e18;
    while(l<r){
        ll mid=(l+r)/2;
        ll cnt=0;
        for(int i=1;i<=m;i++)cnt+=mid/t[i];
        if(cnt<n)l=mid+1;
        else r=mid;
    }
    cout << l;
}
