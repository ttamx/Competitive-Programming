#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    for(int i=2;i*i<=n;i++){
        if(n%i==0){
            cout << n/i << " " << n-n/i << "\n";
            return;
        }
    }
    cout << 1 << " " << n-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}