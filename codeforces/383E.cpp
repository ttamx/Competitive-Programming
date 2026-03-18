#include<bits/stdc++.h>

using namespace std;

const int N=1<<24;

int n;
int dp[N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        sort(s.begin(),s.end());
        s.erase(unique(s.begin(),s.end()),s.end());
        for(int mask=1;mask<(1<<s.size());mask++){
            int cur=0;
            for(int j=0;j<s.size();j++){
                if(mask>>j&1){
                    cur|=1<<(s[j]-'a');
                }
            }
            dp[cur]+=__builtin_popcount(mask)%2?1:-1;
        }
    }
    for(int j=0;j<24;j++){
        for(int i=0;i<N;i++){
            if(i>>j&1){
                dp[i]+=dp[i^(1<<j)];
            }
        }
    }
    long long ans=0;
    for(int i=0;i<N;i++){
        ans^=1LL*dp[i]*dp[i];
    }
    cout << ans << "\n";
}