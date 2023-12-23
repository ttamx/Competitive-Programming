#include<bits/stdc++.h>

using namespace std;

const int mod=1e9+7;

int n;
int c1,c2,c3;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        if(x==1){
            c1++;
        }else if(x==2){
            c2=(c2*2+c1)%mod;
        }else{
            c3=(c3+c2)%mod;
        }
    }
    cout << c3 << "\n";
}