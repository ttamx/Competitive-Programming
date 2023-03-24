#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b,c;
    cin >> a >> b >> c;
    if(a+b==c)cout << "+\n";
    else cout << "-\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}