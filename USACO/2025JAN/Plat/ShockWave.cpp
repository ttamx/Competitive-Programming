#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=5e5+5;
const ll INF=LLONG_MAX/2;

int n;
ll mn,mx;
ll a[N],b[N];

bool check(ll mid){
    for(int i=1;i<=n;i++){
        if(b[i]>mid*(i-1)&&b[i]>mid*(n-i))return false;
    }
    return true;
}

ll solve(){
    ll l=0,r=(mx+n-2)/(n-1)*2;
    while(l<r){
        ll m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    return l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        cin >> n;
        mn=INF,mx=0;
        for(int i=1;i<=n;i++){
            cin >> a[i];
            mn=min(mn,a[i]);
            mx=max(mx,a[i]);
        }
        for(int j=1;j<=n;j++){
            b[j]=a[j];
        }
        ll ans=solve();
        for(int i=1;i<=n;i++){
            for(int j=1;j<=n;j++){
                b[j]=max(0LL,a[j]-abs(i-j));
            }
            ans=min(ans,solve()+1);
        }
        cout << ans << "\n";
    }
}