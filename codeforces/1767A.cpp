#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a1,a2,b1,b2,c1,c2;
    cin >> a1 >> a2 >> b1 >> b2 >> c1 >> c2;
    if((a1==b1&&b2==c2)||(c1==b1&&b2==a2)||(a1==c1&&c2==b2)||(b1==c1&&c2==a2)||(b1==a1&&a2==c2)||(c1==a1&&a2==b2))cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}