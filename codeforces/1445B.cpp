#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    cout << max(a+b,c+d) << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}