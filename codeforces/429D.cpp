#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    for(int i=1;i<n;i++)a[i]+=a[i-1];
    set<pair<ll,ll>> s;
    ll ans=1e18;
    for(ll i=0,j=0;i<n;i++){
        while(j<i&&(i-j)*(i-j)>ans){
            s.erase({a[j],j});
            j++;
        }
        ll d=sqrt(ans);
        while(d*d<ans)d++;
        while(d*d>ans)d--;
        for(auto it=s.lower_bound(make_pair(a[i]-d,LLONG_MIN));it!=s.end()&&it->first<=a[i]+d;it++){
            ans=min(ans,(i-it->second)*(i-it->second)+(a[i]-it->first)*(a[i]-it->first));
        }
        s.emplace(a[i],i);
    }
    cout << ans << "\n";
}