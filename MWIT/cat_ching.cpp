#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> t(n+1);
    for(int i=1;i<=n;i++)cin >> t[i];
    string ans="CHING";
    for(int i=2;i<=n;i++){
        if(i%2==1&&t[i]<=t[i/2])ans="NO";
        if(i%2==0&&t[i]>=t[i/2])ans="NO";
    }
    cout << ans;
}