#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        ll a,b,c,d,e,f;
        cin >> a >> b >> c >> d >> e >> f;
        a-=1970,b--,c--;
        cout << ((((((a*13)+b)*28)+c)*24+d)*60+e)*60+f << "\n";
    }
}