#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int a;
        ll b;
        cin >> a >> b;
        a%=9;
        int res=1;
        while(b){
            if(b&1)res=res*a%9;
            a=a*a%9;
            b>>=1;
        }
        cout << (res?res:9) << "\n";
    }
}