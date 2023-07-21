#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    char c;
    int n;
    cin >> n >> c >> s;
    for(int i=0;i<n;i++){
        if(s[i]<c){
            cout << s.substr(0,i) << c << s.substr(i,n) << "\n";
            return;
        }
    }
    cout << s << c << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}