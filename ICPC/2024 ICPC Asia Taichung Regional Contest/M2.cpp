#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;

using ll = long long;
const ll N=1e6+5;

template<class T>
using oredered_set = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    ll n;
    cin >> n;
    ll ans=n*n;
    vector<ll> a(n+2);
    for (ll i=1;i<=n;i++) cin >> a[i];
    a[0]=-1e18;
    a[n+1]=1e18;
    if(is_sorted(a.begin(),a.end())){
        cout << 0;
        exit(0);
    }
    for(int t=0;t<2;t++){
        vector<ll> dps(n+2);
        // set<pair<ll,ll>> s;
        oredered_set<ll> s;
        auto pmx=a;
        auto smn=a;
        for (ll i=1;i<=n+1;i++) pmx[i]=max(pmx[i-1],pmx[i]);
        for (ll i=n;i>=0;i--) smn[i]=min(smn[i+1],smn[i]);
        dps[n+1]=n+1;
        for (ll i=n;i>0;i--) {
            if (a[i]<=a[i+1] && a[i]<=smn[i]) dps[i]=dps[i+1];
            else dps[i]=i;
            // cout << dps[i] << ' ';
        }
        // cout << '\n';
        s.clear();
        for (ll i=0;i<=n;i++){
            ll nv=i*i;
            if (i) s.insert(a[i]);
            if (pmx[i]<=smn[i+1]){
                nv+=ll(n-dps[i+1]+1ll)*ll(n-dps[i+1]+1ll);
                // cout << " => " << i << ' ' << dps[i] << '\n';
            }
            else{
                ll id = s.order_of_key(*s.upper_bound(smn[i+1])) + 1;
                nv+=ll(n-id+1ll)*ll(n-id+1ll);
                // cout << " => " << i << ' ' << id << '\n';
            }
            ans=min(ans,nv);
        }
        reverse(a.begin(),a.end());
        for(auto &x:a){
            x=-x;
        }
    }
    cout << ans;
}