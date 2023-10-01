#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int ans=1,cnt=1;
    for(int i=1;i<n;i++){
        if(s[i]==s[i-1])cnt++;
        else cnt=1;
        ans=max(ans,cnt);
    }
    cout << ans+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}