#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    map<string,int> mp;
    int mx=0;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        mx=max(mx,++mp[s]);
    }
    for(auto [x,y]:mp){
        if(y==mx){
            cout << x << "\n";
        }
    }
}