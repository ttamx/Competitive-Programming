#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k;
    if(n%k){
        cout << 1 << "\n";
        cout << n << "\n";
    }else{
        cout << 2 << "\n";
        cout << n-1 << " " << 1 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}