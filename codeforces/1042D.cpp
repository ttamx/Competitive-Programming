#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n;
ll k;
ll a[N],b[N];

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    int query(int l,int r){
        return query(r)-query(l-1);
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        a[i]+=a[i-1];
        b[i]=a[i];
    }
    sort(b,b+n+1);
    ll ans=0;
    for(int i=1;i<=n;i++){
        f.update(lower_bound(b,b+n+1,a[i-1])-b+1,+1);
        ans+=f.query(upper_bound(b,b+n+1,a[i]-k)-b+1,n+1);
    }
    cout << ans << "\n";
}