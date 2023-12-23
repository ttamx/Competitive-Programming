#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    for(int i=0;i<n;i++)if(s.substr(i,3)=="...")return void(cout << "2\n");
    int ans=0;
    for(auto x:s)ans+=x=='.';
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}