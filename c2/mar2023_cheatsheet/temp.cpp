#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    sort(s.begin(),s.end());
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();

    
}