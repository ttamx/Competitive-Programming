#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    ll n;
    int m,k;
    cin >> n >> m >> k;
    vector<ll> v(m+1);
    v[0]=1;
    for(int i=1;i<=m;i++)cin >> v[i];
    while(k--){
        ll x;
        int col;
        cin >> x >> col;
        int l=upper_bound(v.begin(),v.end(),x)-v.begin()-1;
        int r=upper_bound(v.begin(),v.end(),x+1)-v.begin()-1;
        if(x==n&&(l&1)==col)m++;
        else if((l&1)==col&&(r&1)==col)m+=2;
    }
    cout << m;
}