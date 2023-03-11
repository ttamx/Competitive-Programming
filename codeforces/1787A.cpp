#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n&1)cout << -1 << '\n';
    else cout << 1 << ' ' << n/2 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}