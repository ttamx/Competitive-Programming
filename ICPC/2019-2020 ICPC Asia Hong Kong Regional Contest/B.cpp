#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        for(int i=1;i<n;i++){
            int x,y;
            cin >> x >> y;
        }
        cout << (n%2?"Alice":"Bob") << "\n";
    }
}