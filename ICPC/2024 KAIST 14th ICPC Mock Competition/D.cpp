#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    ll v1=2,v2=1;
    ll d1=n*2,d2=n*2-2;
    for(int i=1;i<=n+2;i++){
        if(i&1){
            cout << v1 << " ";
            v1+=d1;
            d1-=4;
        }else{
            cout << v2 << " ";
            v2+=d2;
            d2-=4;
        }
    }
}