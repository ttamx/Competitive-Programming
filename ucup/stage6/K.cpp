#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,s;
    cin >> n >> s;
    s--;
    vector<pair<ll,ll>> a(n);
    ll sx=0,sy=0;
    for(int i=0;i<n;i++){
        ll x,y;
        cin >> x >> y >> a[i].first >> a[i].second;
        sx+=a[i].first-x;
        sy+=a[i].second-y;
        if(i==s){
            sx+=2*x;
            sy+=2*y;
        }
    }
    sx/=2;
    sy/=2;
    cout << find(a.begin(),a.end(),make_pair(sx,sy))-a.begin()+1 << "\n";
}