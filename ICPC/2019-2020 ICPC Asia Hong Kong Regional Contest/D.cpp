#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int k;
        ll x;
        cin >> k >> x;
        ll tot=1;
        for(int d=0;;d++){
            tot*=k;
            if(tot<x){
                x-=tot;
                continue;
            }
            x--;
            for(tot/=k;tot>0;tot/=k){
                cout << x/tot+10-k;
                x%=tot;
            }
            break;
        }
        cout << "\n";
    }
}