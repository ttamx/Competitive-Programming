#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string a,b;
    cin >> a >> b;
    string x="",y="";
    for(int i=0;i<b.size()/gcd(a.size(),b.size());i++)x+=a;
    for(int i=0;i<a.size()/gcd(a.size(),b.size());i++)y+=b;
    if(x==y)cout << x << "\n";
    else cout << "-1\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}