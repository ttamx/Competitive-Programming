#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    cout << min({d/a,e/b,f/c});
}