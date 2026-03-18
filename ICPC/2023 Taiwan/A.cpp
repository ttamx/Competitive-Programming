#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        int v=0,mul=1;
        reverse(s.begin(),s.end());
        for(int i=0;i<s.size();i+=3){
            auto t=s.substr(i,3);
            reverse(t.begin(),t.end());
            v+=mul*stoi(t);
            mul=-mul;
        }
        cout << abs(v) << " " << (v%13==0?"YES":"NO") << "\n";
    }
}