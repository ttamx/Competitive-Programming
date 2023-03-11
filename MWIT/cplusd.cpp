#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    string a,b;
    cin >> a >> b;
    reverse(a.begin(),a.end());
    reverse(b.begin(),b.end());
    string c="";
    int res=0;
    int i;
    for(i=0;i<min(a.size(),b.size());i++){
        int num=a[i]+b[i]-96+res;
        res=num/10;
        c=char(num%10+48)+c;
    }
    for(;i<a.size();i++){
        int num=a[i]-48+res;
        res=num/10;
        c=char(num%10+48)+c;
    }
    for(;i<b.size();i++){
        int num=b[i]-48+res;
        res=num/10;
        c=char(num%10+48)+c;
    }
    if(res)c=char(res%10+48)+c;
    cout << c;
}