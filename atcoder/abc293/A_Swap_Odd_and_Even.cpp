#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    for(int i=0;i<s.size();i++)swap(s[2*i],s[2*i+1]);
    cout << s;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}