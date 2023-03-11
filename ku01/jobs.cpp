#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int a=0,b=0;
    for(int i=0,x;i<n;i++){
        cin >> x;
        if(x>18)a++;
        else b++;
    }
    if(a>b)cout << a*2-1;
    else cout << n;
}