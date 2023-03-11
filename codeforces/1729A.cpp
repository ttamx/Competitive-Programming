#include<bits/stdc++.h>

using namespace std;

int t;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> t;
    while(t--){
        int a,b,c;
        cin >> a >> b >> c;
        int x=a;
        int y=abs(b-c)+c;
        if(x<y)cout << 1 << '\n';
        if(y<x)cout << 2 << '\n';
        if(y==x)cout << 3 << '\n';
    }
}
