#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<string> v;
    for(int i=0;i<2*n-2;i++){
        string s;
        cin >> s;
        if(s.size()==n-1)v.emplace_back(s);
    }
    string s;
    if(n==2)s=v[0]+v[1];
    else if(v[0].substr(1,n-2)==v[1].substr(0,n-2))s=v[0][0]+v[1];
    else s=v[1][0]+v[0];
    auto ss=s;
    reverse(s.begin(),s.end());
    if(s==ss)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}