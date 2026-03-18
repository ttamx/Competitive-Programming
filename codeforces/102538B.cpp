#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--){
        int n;
        cin >> n;
        vector<int> a(n);
        for(auto &x:a){
            cin >> x;
        }
        if(n==2){
            cout << 1 << "\n";
        }else{
            cout << min(n/2,n-(int)count(a.begin(),a.end(),1)) << "\n";
        }
    }
}