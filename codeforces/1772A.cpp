#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    cout << s[0]+s[2]-96 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}