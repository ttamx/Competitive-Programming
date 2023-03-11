#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    if(n<m){
        cout << "NEED MORE GEMS!";
        return 0;
    }
    cout << "You get a SCEPTER!\n";
    n-=m;
    cout << "SSR : " << n/10 << '\n';
    n%=10;
    cout << "SR : " << n/5 << '\n';
    n%=5;
    cout << "R : " << n/2 << '\n';
    n%=2;
    cout << "C : " << n;
}