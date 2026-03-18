#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const ll INF=1e18;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,c1,c2;
    cin >> n >> c1 >> c2;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll ans=INF;
    for(int t=0;t<2;t++){
        for(int d=-1;d<=1;d++){
            vector<int> vals;
            int x=a[0]+d;
            for(int i=2;i*i<=x;i++){
                if(x%i)continue;
                vals.emplace_back(i);
                while(x%i==0)x/=i;
            }
            if(x>1)vals.emplace_back(x);
            for(auto g:vals){
                array<ll,3> dp{};
                dp[0]=dp[1]=dp[2]=abs(d)*c2;
                for(int i=1;i<n;i++){
                    ll cost=INF;
                    if(a[i]%g==0)cost=0;
                    else if((a[i]-1)%g==0)cost=c2;
                    else if((a[i]+1)%g==0)cost=c2;
                    dp[0]=min(dp[0]+cost,INF);
                    dp[1]=min(dp[0],dp[1]+c1);
                    dp[2]=min(dp[1],dp[2]+cost);
                }
                ans=min(ans,dp[2]);
            }
        }
        reverse(a.begin(),a.end());
    }
    cout << ans << "\n";
}