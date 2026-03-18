#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int n=s.size();
    string ans="";
    for(int i=0;i<n-1;i++){
        ans.push_back(s[i+1]);
        if(s[i]!=s[i+1]){
            ans.push_back(s[i]);
        }
    }
    cout << ans << "\n";
}