#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    for(auto &x:s)x=tolower(x);
    string res="";
    res.push_back(s[0]);
    for(int i=1;i<n;i++)if(s[i]!=s[i-1])res.push_back(s[i]);
    cout << (res=="meow"?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}