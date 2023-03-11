#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s;
    cin >> s;
    vector<ll> a;
    ll res=0,mul=1;
    for(int i=1;i<s.size();i++){
        if(s[i]==','||s[i]==']'){
            a.push_back(res*mul);
            res=0,mul=1;
            continue;
        }
        if(s[i]=='-'){
            mul=-1;
            continue;
        }
        res*=10;
        res+=s[i]-'0';
    }
    sort(a.rbegin(),a.rend());
    for(auto x:a)cout << x << ' ';
}