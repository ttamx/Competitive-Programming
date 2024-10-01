#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    int cnt[300]={};
    for(auto x:s)cnt[x]++;
    cout << min({cnt['T'],cnt['P'],cnt['A']+cnt['U']});
}