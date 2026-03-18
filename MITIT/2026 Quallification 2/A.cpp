#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    string s;
    cin >> n >> s;
    int cost=s[0]!='M';
    rotate(s.begin(),find(s.begin(),s.end(),'M'),s.end());
    for(int i=1;i<s.size();i++){
        if(s[i]!="TI"[i%2]){
            cout << -1 << "\n";
            return;
        }
    }
    cout << cost << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}