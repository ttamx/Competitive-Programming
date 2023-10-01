#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b;
    cin >> a >> b;
    cout << 2 << '\n';
    cout << a-1 << ' ' << 1 << '\n';
    cout << a << ' ' << b << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}