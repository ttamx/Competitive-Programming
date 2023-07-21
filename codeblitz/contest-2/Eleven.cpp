#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int val=0;
    for(auto x:s){
        val*=10;
        val+=x-'0';
        val%=11;
    }
    cout << (val==0?"Yes":"No") << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}