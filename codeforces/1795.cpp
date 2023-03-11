#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b;
    cin >> a >> b;
    string s1,s2;
    cin >> s1 >> s2;
    for(int i=b-1;i>=0;i--)s1=s1+s2[i];
    int cnt=0;
    for(int i=1;i<a+b;i++)if(s1[i]==s1[i-1])cnt++;
    cout << (cnt<=1?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}