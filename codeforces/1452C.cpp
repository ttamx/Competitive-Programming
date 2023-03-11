#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int cnt1=0,cnt2=0,ans=0;
    for(auto &c:s){
        if(c=='[')++cnt1;
        else if(c==']'&&cnt1)--cnt1,++ans;
        else if(c=='(')++cnt2;
        else if(c==')'&&cnt2)--cnt2,++ans;
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}