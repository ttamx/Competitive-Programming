#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int mn=s[0],idx=0;
    for(int i=0;i<n;i++){
        if(s[i]<=mn){
            mn=s[i];
            idx=i;
        }
    }
    cout << s[idx];
    for(int i=0;i<n;i++)if(i!=idx)cout << s[i];
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}