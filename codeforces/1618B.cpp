#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string ans;
    cin >> ans;
    for(int i=3;i<n;i++){
        string s;
        cin >> s;
        if(ans.back()==s[0])ans=ans+s[1];
        else ans=ans+s;
    }
    if(ans.size()<n)ans=ans+'a';
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}