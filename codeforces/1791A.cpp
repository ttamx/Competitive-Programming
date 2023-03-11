#include<bits/stdc++.h>

using namespace std;

string cf="codeforces";

void runcase(){
    char c;
    cin >> c;
    bool ok=false;
    for(auto x:cf)if(c==x)ok=true;
    cout << (ok?"YES\n":"NO\n");
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}