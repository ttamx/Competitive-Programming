#include<bits/stdc++.h>

using namespace std;

bool isvowel(char c){
    return (c=='a'||c=='e'||c=='i'||c=='o'||c=='u');
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        string s;
        cin >> s;
        int len=s.size();
        string a,b,c,d,e;
        int idx=0;
        while(idx<len&&!isvowel(s[idx]))a=a+s[idx++];
        while(idx<len&&isvowel(s[idx]))b=b+s[idx++];
        int pos=len-1;
        while(pos>=idx&&!isvowel(s[pos]))e=s[pos--]+e;
        while(pos>=idx&&isvowel(s[pos]))d=s[pos--]+d;
        while(idx<=pos)c=c+s[idx++];
        cout << a << d << c << b << e << '\n';
    }
}