#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    map<string,int> mp;
    for(int i=0;i<n;i++){
        string s;
        cin >> s;
        int pos=0;
        while(s[pos]!='*')pos++;
        for(char c='a';c<='z';c++){
            s[pos]=c;
            mp[s]++;
        }
    }
    int mx=0;
    string  ans="";
    for(auto [w,c]:mp){
        if(c>mx){
            mx=c;
            ans=w;
        }
    }
    cout << ans << " " << mx << "\n";
}