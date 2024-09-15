#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<long long> qs(n+1);
    for(int i=0;i<n;i++){
        qs[i+1]=qs[i]+1LL*a[i]*a[i];
    }
    for(auto &x:b){
        cin >> x;
    }
    int lg=1;
    while((1<<lg)<=n){
        lg++;
    }
    vector<vector<int>> dp(lg,vector<int>(n));
    dp[0]=b;
    for(int i=1;i<lg;i++){
        for(int j=0;j+(1<<i)<=n;j++){
            dp[i][j]=dp[i-1][j]|dp[i-1][j+(1<<(i-1))];
        }
    }
    auto query=[&](int l,int r){
        int k=31-__builtin_clz(r-l+1);
        return dp[k][l]|dp[k][r-(1<<k)+1];
    };
    long long ans=0;
    for(int i=0;i<n;i++){
        for(int j=i;j>=0;j--){
            int cur=query(j,i);
            int l=0,r=j;
            while(l<r){
                int m=(l+r)/2;
                if(query(m,j)==cur){
                    r=m;
                }else{
                    l=m+1;
                }
            }
            int idx=upper_bound(qs.begin(),qs.end(),qs[i+1]-1LL*cur*cur)-qs.begin();
            idx=max(idx,l);
            ans+=max(0,j-idx+1);
            j=l;
        }
    }
    cout << ans << "\n";
}