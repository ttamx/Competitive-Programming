#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int n=s.size();
    for(int i=0;i<n;i++){
        if(s[i]=='?'){
            if((i>0&&s[i-1]=='1')||(i<n-1&&s[i+1]=='1'))s[i]='1';
            else s[i]='0';
        }
    }
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}