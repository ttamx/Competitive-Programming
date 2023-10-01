#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n;
    map<string,int> mp;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        mp[s]++;
    }
    cin >> k;
    for(int i=1;i<=k;i++){
        string s;
        cin >> s;
        if(mp[s]--==0){
            cout << i;
            return 0;
        }
    }
    cout << "OK";
}