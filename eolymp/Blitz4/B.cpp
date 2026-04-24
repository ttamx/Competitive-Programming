#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=999983;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n >> s;
        ll ans=1;
        for(auto x:s){
            x-='0';
            if(x>0){
                while(x%2==0){
                    x/=2;
                }
                int c=1;
                while(x*2<10){
                    x*=2;
                    c++;
                }
                ans=ans*c%MOD;
            }
        }
        cout << ans << "\n";
    }
}