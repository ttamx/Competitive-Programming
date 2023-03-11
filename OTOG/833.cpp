#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    while(cin >> s){
        int res=0;
        for(auto x:s){
            res*=2;
            if(x=='-')res++;
        }
        cout << char('a'+res-1);
    }
}