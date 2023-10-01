#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    map<ll,ll> mp;
    for(int i=0;i<n;i++){
        ll x;
        cin >> x;
        mp[x]++;
    }
    int q;
    cin >> q;
    while(q--){
        ll x,y;
        cin >> x >> y;
        ll v=x*x-4*y;
        if(v<0){
            cout << 0 << " ";
            continue;
        }
        ll w=sqrtl(v);
        if(w*w!=v||(x+w)%2!=0){
            cout << 0 << " ";
            continue;
        }
        ll a=(x+w)/2;
        ll b=(x-w)/2;
        if(a==b)cout << mp[a]*(mp[a]-1)/2 << " ";
        else cout << mp[a]*mp[b] << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}