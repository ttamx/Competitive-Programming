#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e6+5;
const int M=5005;

int n,m,k;
int a[N],b[N];
int h[M],d[M],c[M];
pair<int,ll> dp[M];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> k;
    for(int i=1;i<=n;i++){
        cin >> a[i] >> b[i];
    }
    for(int i=1;i<=m;i++){
        cin >> h[i] >> d[i] >> c[i];
    }
    for(int i=1;i<=m;i++){
        for(int j=k;j>=c[i];j--){
            auto cur=dp[j-c[i]];
            int id=cur.first%n+1;
            if(b[id]){
                ll t=(h[i]-1)/b[id];
                cur.second+=t*d[i];
                if(cur.second>=a[id]){
                    cur.first++;
                    cur.second=0;
                }
            }else{
                cur.first++;
                cur.second=0;
            }
            dp[j]=max(dp[j],cur);
        }
    }
    ll ans=0;
    for(int i=0;i<dp[k].first;i++){
        ans+=a[i%n+1];
    }
    cout << dp[k].second << " " << ans+dp[k].second << "\n";
}