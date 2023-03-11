#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    int l=0,r=n-1;
    while(l<r){
        if(s[l]!=s[r])l++,r--;
        else break;
    }
    cout << r-l+1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}