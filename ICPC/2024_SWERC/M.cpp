#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    for(auto x:s){
        cout << (x=='K'?".-":".-.-");
    }
}