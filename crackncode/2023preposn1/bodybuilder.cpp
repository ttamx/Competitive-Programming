#include<bits/stdc++.h>

using namespace std;

const int N=20;

int n,m;
int s[N],w[N];
bool dp[1<<20];
int ans[22];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=0;i<n;i++)cin >> s[i] >> w[i];
    dp[0]=true;
    ans[1]=n;
    for(int i=1;i<1<<n;i++){
        if(__builtin_popcount(i)==1){
            dp[i]=true;
            continue;
        }
        for(int j=0;j<n;j++)if(i>>j&1){
            int b=i^(1<<j);
            if(!dp[b])continue;
            bool ok=true;
            for(int k=0;k<n;k++)if(b>>k&1){
                if(s[k]>=s[j]&&w[k]<=w[j])ok=false;
                if(s[k]<=s[j]&&w[k]>=w[j])ok=false;
            }
            dp[i]=ok;
        }
        ans[__builtin_popcount(i)]+=dp[i];
    }
    while(m--){
        int x;
        cin >> x;
        cout << ans[x] << "\n";
    }
}