#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

int n;
ll x[N],y[N],z[N];
vector<ll> vec;
ll ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> x[i] >> y[i] >> z[i];
    sort(x+1,x+n+1);
    sort(y+1,y+n+1);
    sort(z+1,z+n+1);
    for(int i=1;i<=n;i++)vec.emplace_back(abs(x[i]-z[n-i+1]));
    sort(vec.begin(),vec.end());
    for(int i=0;i<n;i++)ans+=(i+1)*vec[i];
    cout << ans*y[n/2+1];
}