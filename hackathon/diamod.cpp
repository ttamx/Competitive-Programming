#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<ll> dp(n+1);
    dp[1]=1;
    for(int i=2;i<=n;i++)dp[i]=dp[i-1]+dp[i-2];
    vector<string> s;
    for(auto x:dp)s.push_back(to_string(x));
    int dig=s[n].size()+1;
    for(int i=1;i<=n;i++){
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(j<n-i+1){
                for(int k=0;k<dig;k++)cout << '_';
            }else{
                cnt++;
                for(int k=0;k<dig-s[cnt].size();k++)cout << '_';
                cout << s[cnt];
            }
        }
        for(int j=n-1;j>=1;j--){
            if(j<n-i+1){
                for(int k=0;k<dig;k++)cout << '_';
            }else{
                cnt--;
                for(int k=0;k<dig-s[cnt].size();k++)cout << '_';
                cout << s[cnt];
            }
        }
        cout << '\n';
    }
    for(int i=n-1;i>=1;i--){
        int cnt=0;
        for(int j=1;j<=n;j++){
            if(j<n-i+1){
                for(int k=0;k<dig;k++)cout << '_';
            }else{
                cnt++;
                for(int k=0;k<dig-s[cnt].size();k++)cout << '_';
                cout << s[cnt];
            }
        }
        for(int j=n-1;j>=1;j--){
            if(j<n-i+1){
                for(int k=0;k<dig;k++)cout << '_';
            }else{
                cnt--;
                for(int k=0;k<dig-s[cnt].size();k++)cout << '_';
                cout << s[cnt];
            }
        }
        cout << '\n';
    }
}
