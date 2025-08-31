#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,p;
    cin >> n >> p;
    string s;
    cin >> s;
    p--;
    if(p>=n/2)p=n-p-1;
    int l=0,r=n/2-1;
    while(l<n/2&&s[l]==s[n-l-1])l++;
    while(r>0&&s[r]==s[n-r-1])r--;
    if(r<l){
        cout << 0 << "\n";
        exit(0);
    }
    int ans=min(abs(p-l),abs(p-r))+r-l;
    for(int i=0;i<n/2;i++){
        int d=abs(s[i]-s[n-i-1]);
        ans+=min(d,26-d);
    }
    cout << ans << "\n";
}