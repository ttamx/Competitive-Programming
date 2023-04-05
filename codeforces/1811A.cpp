#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    string s;
    cin >> n >> m;
    cin >> s;
    bool ok=false;
    for(auto x:s){
        if(!ok&&m+'0'>x)cout << m,ok=true;
        cout << x;
    }
    if(!ok)cout << m;
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}