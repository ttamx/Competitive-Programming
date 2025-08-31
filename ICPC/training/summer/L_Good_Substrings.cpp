#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    string a;
    cin >> a;
    int k;
    cin >> k;
    int n=s.size();
    vector<vector<int>> lcp(n,vector<int>(n));
    for(int i=n-1;i>=0;i--){
        for(int j=0;j<n;j++){
            if(s[i]==s[j]){
                lcp[i][j]=(i+1<n&&j+1<n?lcp[i+1][j+1]+1:1);
            }
        }
    }
    int ans=0;
    for(int i=0;i<n;i++){
        int p=i;
        for(int j=0;j<i;j++){
            p=max(p,i+lcp[i][j]);
        }
        int cnt=0;
        for(int j=i;j<n;j++){
            if(a[s[j]-'a']=='0'){
                cnt++;
                if(cnt>k)break;
            }
            if(j>=p){
                ans++;
            }
        }
    }
    cout << ans << "\n";
}