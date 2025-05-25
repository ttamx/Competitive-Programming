#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    for(int i=0,t=0;i<n;i++,t^=1){
        if(t){
            if(i+1>=n||s[i]!=s[i+1]){
                cout << "NO\n";
                return;
            }
            i++;
        }
    }
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}