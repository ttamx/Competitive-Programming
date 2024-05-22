#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

int n,x;
int a[N],dp[N];
vector<int> v1,v2;
int ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> x;
    for(int i=1;i<=n;i++)cin >> a[i];
    for(int i=1;i<=n;i++){
        auto it=lower_bound(v1.begin(),v1.end(),a[i]);
        dp[i]=it-v1.begin()+1;
        if(it==v1.end())v1.emplace_back(a[i]);
        else *it=a[i];
    }
    for(int i=n;i>=1;i--){
        auto it=lower_bound(v2.begin(),v2.end(),-a[i]);
        ans=max(ans,dp[i]+int(it-v2.begin()));
        a[i]+=x;
        it=lower_bound(v2.begin(),v2.end(),-a[i]);
        if(it==v2.end())v2.emplace_back(-a[i]);
        else *it=-a[i];
    }
    cout << ans;
}