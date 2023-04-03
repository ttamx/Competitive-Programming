#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    ll c,d;
    cin >> n >> c >> d;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    a.emplace_back(0);
    sort(a.begin(),a.end());
    ll ans=n*c+d;
    ll pre=0;
    for(int i=1;i<=n;i++){
        if(a[i]==a[i-1]){
            pre+=c;
            continue;
        }
        ll res=(a[i]-a[i-1]-1)*d+pre;
        ans=min(ans,res+c*(n-i));
        pre=res;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}