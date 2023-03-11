#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    ll x,y;
    cin >> n >> x >> y;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    a.push_back(-1);
    sort(a.begin(),a.end());
    vector<ll> v(n+1);
    for(int i=1;i<=n;i++)v[i]=v[i-1]+a[i]-a[i-1]-1;
    for(int i=2;i<=n;i++)v[i]=max(v[i-1],v[i]);
    ll ans=0;
    while(x<y){
        int idx=upper_bound(v.begin(),v.end(),x)-v.begin()-1;
        if(x+idx>=y){
            ans+=y-x;
            break;
        }
        if(idx<=n-idx){
            ans=-1;
            break;
        }
        ll add=2*idx-n;
        ll nxt=y-idx;
        if(idx<n)nxt=min(nxt,v[idx+1]);
        ll cnt=(nxt-x+add-1)/add;
        ans+=cnt*n;
        x+=cnt*add;
    }
    cout << ans <<'\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}