#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    long long res=0;
    for(int i=1;i<n;i++){
        long long x;
        cin >> x;
        res|=x;
    }
    for(int i=2;i<=n;i++)cout << "WB"[res>>(n-i)&1];
}