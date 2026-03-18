#include<bits/stdc++.h>

using namespace std;

int main(){
    string s;
    cin >> s;
    int n=s.size();
    vector<int> pos(256,n);
    for(int i=n-1;i>=0;i--){
        pos[s[i]]=i;
    }
    for(char c='b';c<='z';c++){
        if(pos[c]<pos[c-1]){
            cout << "NO\n";
            exit(0);
        }
    }
    cout << "YES\n";
}