#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n;
    ll m;
    cin >> n >> m;
    vector<ll> a(n+1),b(n+1);
    ll w=1,v=0;
    for(int i=1;i<=n;i++){
        cin >> b[i];
        a[i]=a[i-1]+b[i];
        if(a[i]*w>v*i){
            v=a[i];
            w=i;
        }
    }
    cerr << w << " " << v << "\n";
    vector<pair<ll,int>> dp(n*n+1,{0LL,-1}),dp2(w,{0LL,-1});
    for(int i=1;i<=n;i++){
        for(int j=i;j<=n*n;j++){
            dp[j]=max(dp[j],make_pair(dp[j-i].first+a[i],i));
        }
    }
    for(int i=1;i<=n;i++){
        if(i==w)continue;
        int g=gcd(i,w);
        for(int s=0;s<g;s++){
            int j=s;
            for(int t=0;t<2*w;t+=g){
                ll c=dp2[j].first+a[i];
                j+=i;
                int d=j/w;
                j-=d*w;
                c-=d*v;
                if(c>dp2[j].first){
                    dp2[j]={c,i};
                }
            }
        }
    }
    auto calc=[&](ll x){
        if(x<=n*n){
            return dp[x].first;
        }else{
            return dp2[x%w].first+(x/w)*v;
        }
    };
    ll l=0,r=m;
    while(l<r){
        ll mid=(l+r)/2;
        if(calc(mid)>=m)r=mid;
        else l=mid+1;
    }
    cout << l << "\n";
    vector<ll> ans(n+1);
    if(l<=n*n){
        cerr << "CASE 1\n";
        ll x=l;
        while(true){
            assert(x>=0);
            int i=dp[x].second;
            if(i==-1)break;
            ans[i]++;
            x-=i;
        }
        assert(x==0);
    }else{
        cerr << "CASE 2\n";
        ll x=l;
        while(x%w>0){
            assert(x>=0);
            int i=dp2[x%w].second;
            if(i==-1)break;
            ans[i]++;
            x-=i;
        }
        assert(x>=0);
        ans[w]+=x/w;
    }
    for(int i=n;i>=1;i--){
        ans[i-1]+=ans[i];
    }
    ll cnt=0;
    for(int i=1;i<=n;i++){
        cout << ans[i] << " \n"[i==n];
        cnt+=ans[i];
    }
    assert(cnt==l);
    cerr << cnt << "\n";
    ll val=0;
    for(int i=1;i<=n;i++){
        val+=ans[i]*b[i];
    }
    cerr << val << " >= " << m << "\n";
    assert(val>=m);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}