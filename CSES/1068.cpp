#include<bits/stdc++.h>

using namespace std;

long long n;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    while(n>1){
        cout << n << " ";
        if(n&1)n=n*3+1;
        else n/=2;
    }
    cout << 1;
}