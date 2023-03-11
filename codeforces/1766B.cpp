#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    if(n<=3){
        cout << "NO\n";
        return;
    }
    map<string,int> mp;
    for(int i=1;i<n;i++){
        if(mp[s.substr(i,2)]){
            cout << "YES\n";
            return;
        }
        mp[s.substr(i-1,2)]++;
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}