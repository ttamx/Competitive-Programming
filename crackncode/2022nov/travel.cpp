#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=1e6+5;

struct fenwick{
    ll f[N];
    void add(int i,ll v){
        while(i<N){
            f[i]=max(f[i],v);
            i+=i&-i;
        }
    }
    ll read(int i){
        ll ret=0;
        while(i){
            ret=max(ret,f[i]);
            i-=i&-i;
        }
        return ret;
    }
}f;

int n;
ll ans;
ll c[N],s[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++)cin >> c[i];
    ll sum=0;
    for(int i=2;i<=n;i++)cin >> s[i],sum+=s[i];
    for(int i=1;i<=n-1;i++){
        sum=sum-s[i];
        f.add(i,sum+c[i]);
    }
    sum=0;
    for(int i=n;i>=2;i--){
        sum=sum+s[i+1];
        ans=max(ans,f.read(i-1)-sum+c[i]);
    }
    cout << ans;
}