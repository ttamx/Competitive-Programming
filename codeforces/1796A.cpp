#include<bits/stdc++.h>

using namespace std;

string f="FBFFBFFBFBFFBFFBFBFFBFFB";

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    for(int i=0;i<f.size();i++){
        if(s==f.substr(i,n)){
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}