#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int x;
    cin >> x;
    if(x>2)cout << x*x*x-14*x+17;
    else if(x>-3)cout << -2*x+1;
    else cout << -(x+4)*(x+4)+8;
}