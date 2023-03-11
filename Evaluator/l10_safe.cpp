#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int prev=1e9;
    while(n--){
        int t,v;
        cin >> t >> v;
        cout << max(0,v-prev) << '\n';
        prev=min(prev,v);
    }
}