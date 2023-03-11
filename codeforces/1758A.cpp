#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    cout << s;
    for(int i=s.size()-1;i>=0;i--)cout << s[i];
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}