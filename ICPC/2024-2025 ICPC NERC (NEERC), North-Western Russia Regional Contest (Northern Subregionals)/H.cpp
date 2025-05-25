#include<bits/stdc++.h>

using namespace std;

const int MOD=998244353;

using ll = long long;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+1),b(n+1);
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    vector<ll> dp1(n+1),dp2(n+1);
    for(int i=1;i<=n;i++){
        dp1[i]=(dp1[i-1]+dp2[i-1]+1)%MOD;
        dp2[i]=(3*dp2[i-1]+2)%MOD;
    }
    int last=n;
    while(last>=1&&a[last]==b[last]){
        last--;
    }
    if(last==0){
        cout << 0 << "\n";
        return;
    }
    auto solve=[&](int pile,vector<int> a){
        ll res=0;
        for(int i=last-1;i>=1;i--){
            if(a[i]==pile)continue;
            if(a[i]==2){
                res=(res+dp2[i-1]+1)%MOD;
                pile^=2;
            }else if(pile==2){
                res=(res+dp1[i-1]+1)%MOD;
                pile=a[i]^2;
            }else{
                res=(res+2*dp2[i-1]+2)%MOD;
            }
        }
        return res;
    };
    ll ans=0;
    if(a[last]==2){
        ans=(solve(b[last]^2,a)+solve(b[last]^2,b)+1)%MOD;
    }else if(b[last]==2){
        ans=(solve(a[last]^2,a)+solve(a[last]^2,b)+1)%MOD;
    }else{
        ans=(solve(a[last]^2,a)+solve(a[last],b)+dp2[last-1]+2)%MOD;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        runcase();
    }
}