#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int idx=0;
    while(idx<n){
        char res=s[idx++];
        while(idx<n&&s[idx]!=res)idx++;
        idx++;
        cout << res;
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}