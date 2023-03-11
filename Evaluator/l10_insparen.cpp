#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string str;
    cin >> str;
    int ans=0,cnt=0;
    for(auto &c:str){
        if(c=='(')++cnt;
        else if(cnt>0)--cnt;
        else ++ans;
    }
    cout << ans+cnt;
}
