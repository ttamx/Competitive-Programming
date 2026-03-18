#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    string s;
    cin >> n >> s;
    int c=0;
    for(int i=0;i<n;i++){
        if(s[i]=='H'){
            c^=i%2+1;
        }
    }
    cout << (c?1:2) << "\n";
}