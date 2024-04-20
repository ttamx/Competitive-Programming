#include<bits/stdc++.h>
 
using namespace std;
 
using ll = long long;
 
const int N=1e5+5;
 
int n,m,p;
ll v[N],w[N],sv[N],sw[N];
 
ll search(int st){
    int l=0,r=1e9;
    while(l<r){
        int mid=(l+r)/2;
        int pos=st;
        for(int i=0;i<p;i++){
            pos=upper_bound(sw+pos,sw+st+m,sw[pos-1]+mid)-sw;
        }
        if(pos>=st+m)r=mid;
        else l=mid+1;
    }
    return l;
}
 
ll pw(ll x){
    return x*x;
}
 
int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> p;
    for(int i=1;i<=n;i++){
        cin >> v[i] >> w[i];
        sv[i]=sv[i-1]+v[i];
        sw[i]=sw[i-1]+w[i];
    }
    ll ans=-1e18;
    for(int i=m;i<=n;i++){
        ans=max(ans,sv[i]-sv[i-m]-pw(search(i-m+1)));
    }
    cout << ans;
}