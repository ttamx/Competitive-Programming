#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<int> ans(n-1,2),dp(n),jum(n,-1),cnt(n+1),hop(n);
    cnt[0]=1;
    for(int i=n-1;i>0;i--){
        if(a[i-1]>0&&cnt[a[i-1]-1]>0)ans[i-1]=min(ans[i-1],1);
        if(i+a[i]+1>n){
            dp[i]=1;
            hop[i]=1;
        }else if(i+a[i]+1==n){
            dp[i]=0;
            jum[i]=1;
            hop[i]=1;
            cnt[1]++;
        }else{
            dp[i]=dp[i+a[i]+1];
            hop[i]=hop[i+a[i]+1]+1;
            if(jum[i+a[i]+1]!=-1){
                jum[i]=jum[i+a[i]+1]+1;
                cnt[jum[i]]++;
            }
        }
        if(jum[i]==a[i-1]){
            ans[i-1]=0;
        }else if(jum[i]!=-1){
            ans[i-1]=1;
        }
    }
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}