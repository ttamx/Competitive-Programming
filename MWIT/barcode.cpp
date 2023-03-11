#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    s=s+"1";
    int res=0,ans=0;
    for(auto x:s){
        if(x=='0')res=1;
        else ans+=res,res=0;
    }
    cout << ans;
}