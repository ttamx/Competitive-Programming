#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string s="UUDDLRLRBAS";
    string a;
    cin >> a;
    int len=a.size();
    int mn=min(11,len);
    int ans=0;
    for(int i=1;i<=mn;++i)if(a.substr(len-i,i)==s.substr(0,i))ans=i;
    cout << s.substr(ans,11-ans);
}