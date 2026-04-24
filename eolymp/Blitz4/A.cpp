#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int MOD=999983;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        string s;
        cin >> n >> s;
        for(int i=1;i<n;i++){
            cout << (s[i]==s[i-1]);
        }
        cout << "\n";
    }
}