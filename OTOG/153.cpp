#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    while(cin >> s)cout << (regex_match(s,regex("da+dd?(i|y)"))?"She called me!!!":"Cooing") << "\n";
}