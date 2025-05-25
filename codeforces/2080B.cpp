#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    ll t;
    cin >> n >> m >> t;
    vector<ll> a(n+1),b(m+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=m;i++){
        cin >> b[i];
    }
    auto c=a;
    for(int i=1;i<=n;i++){
        c[i]+=c[i-1];
    }
    ll ans=0;
    int last=1;
    for(int i=1;i<=m;i++){
        while(last<=b[i]){
            ll d=c[b[i]]-c[last];
            if(d<=t){
                ll rem=t-d;
                ans=max(ans,b[i]-last+(rem/a[last]));
            }
            last++;
        }
    }
    last=n;
    for(int i=m;i>=1;i--){
        while(last>=b[i]){
            ll d=c[last-1]-c[b[i]-1];
            if(d<=t){
                ll rem=t-d;
                ans=max(ans,last-b[i]+(rem/a[last]));
            }
            last--;
        }
    }
    cout << ans << "\n";
}