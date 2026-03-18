#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int k;
    cin >> k;
    string s;
    cin >> s;
    int cnt[256]={};
    for(auto x:s){
        cnt[x]++;
    }
    string t="";
    for(int i='a';i<='z';i++){
        if(cnt[i]%k){
            cout << -1 << "\n";
            exit(0);
        }
        t+=string(cnt[i]/k,i);
    }
    for(int i=0;i<k;i++){
        cout << t;
    }
    cout << "\n";
}