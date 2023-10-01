#include<bits/stdc++.h>
 
using namespace std;
 
typedef long long ll;
 
const int N=45;
const int M=(1<<20)+5;
 
int n,k,k2;
ll x,a[N];
vector<ll> l,r;
ll ans;
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x;
    for(int i=0;i<n;i++)cin >> a[i];
    k=n/2;
    k2=n-k;
    for(int i=0;i<1<<k;i++){
        ll sum=0;
        for(int j=0;j<k;j++)if(i>>j&1)sum+=a[j];
        l.emplace_back(sum);
    }
    for(int i=0;i<1<<k2;i++){
        ll sum=0;
        for(int j=0;j<k2;j++)if(i>>j&1)sum+=a[j+k];
        r.emplace_back(sum);
    }
    sort(l.begin(),l.end());
    sort(r.begin(),r.end());
    for(auto v:l)ans+=upper_bound(r.begin(),r.end(),x-v)-lower_bound(r.begin(),r.end(),x-v);
    cout << ans;
}