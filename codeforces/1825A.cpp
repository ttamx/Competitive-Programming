#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string s;
    cin >> s;
    int l=0,r=s.size()-1;
    for(int i=1;i<r;i++)if(s[i]!=s[i-1]){
        cout << r << "\n";
        return;
    }
    cout << -1 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}