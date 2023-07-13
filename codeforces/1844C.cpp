#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    ll sum1=0,sum2=0,mx=-1e18;
    for(auto x:a)mx=max(mx,x);
    for(int i=0;i<n;i+=2)if(a[i]>0)sum1+=a[i];
    for(int i=1;i<n;i+=2)if(a[i]>0)sum2+=a[i];
    if(mx<0)cout << mx << "\n";
    else cout << max(sum1,sum2) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}