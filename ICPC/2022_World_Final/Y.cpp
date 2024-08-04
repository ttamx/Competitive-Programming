#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    string t="";
    for(auto x:s){
        if(t.empty()||x!=t.back())t.push_back(x);
    }
    while(t.size()>3){
        t.pop_back();
        t.pop_back();
    }
    cout << t;
}