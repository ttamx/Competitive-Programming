#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    string s;
    cin >> s;
    vector<bool> a(26),b(26);
    for(int i=0;i<n;i+=2)a[s[i]-'a']=true;
    for(int i=1;i<n;i+=2)b[s[i]-'a']=true;
    for(int i=0;i<26;i++)if(a[i]&&b[i])return void(cout << "NO\n");
    cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}