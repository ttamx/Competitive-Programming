#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    if(s[0]=='0')return void(cout << 0 << '\n');
    long long ans=1;
    if(s[0]=='?')ans*=9;
    for(int i=1;i<s.size();i++)if(s[i]=='?')ans*=10;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}