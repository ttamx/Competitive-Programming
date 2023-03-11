#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int ans=1;
    cout << 1 << ' ';
    for(int i=1;i<n-1;i++){
        if(s[i]!=s[i-1])ans=i+1;
        cout << ans << ' ';
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}