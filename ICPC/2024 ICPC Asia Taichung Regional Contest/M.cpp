#include <bits/stdc++.h>

using namespace std;

using ll = long long;
const ll N=1e6+5;

struct Fenwick{
    int t[N];
    void init(int n){
        for(int i=1;i<=n;i++){
            t[i]=0;
        }
    }
    void update(int i,int v){
        for(i++;i<N;i+=i&-i){
            t[i]+=v;
        }
    }
    int query(int i){
        int res=0;
        for(i++;i>0;i-=i&-i){
            res+=t[i];
        }
        return res;
    }
}f;

signed main() {
    cin.tie(nullptr)->ios::sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    if(a==b){
        cout << 0;
        exit(0);
    }
    ll ans=1LL*n*n;
    for(int t=0;t<2;t++){
        auto b=a;
        sort(b.begin(),b.end());
        for(auto &x:a){
            x=lower_bound(b.begin(),b.end(),x)-b.begin();
        }
        auto pmx=a;
        auto smn=a;
        for(int i=1;i<n;i++){
            pmx[i]=max(pmx[i],pmx[i-1]);
        }
        for(int i=n-2;i>=0;i--){
            smn[i]=min(smn[i],smn[i+1]);
        }
        vector<int> dp(n);
        dp[n-1]=0;
        for(int i=n-2;i>=0;i--){
            if(a[i]<=smn[i+1]){
                dp[i]=dp[i+1];
            }else{
                dp[i]=n-i;
            }
        }
        f.init(n);
        for(int i=0;i+1<n;i++){
            f.update(a[i],+1);
            ll base=1LL*(i+1)*(i+1);
            if(pmx[i]<=smn[i+1]){
                base+=1LL*dp[i+1]*dp[i+1];
            }else{
                int d=n-f.query(smn[i+1]);
                base+=1LL*d*d;
            }
            ans=min(ans,base);
        }
        reverse(a.begin(),a.end());
        for(auto &x:a){
            x=-x;
        }
    }
    cout << ans;
}