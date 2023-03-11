#include<bits/stdc++.h>

using namespace std;

void runcase(){
    string a,b;
    cin >>  a >> b;
    int al=a.size(),bl=b.size();
    int x,y;
    if(a[al-1]=='S')x=1;
    else if(a[al-1]=='M')x=2;
    else x=3;
    if(b[bl-1]=='S')y=1;
    else if(b[bl-1]=='M')y=2;
    else y=3;
    if(a==b){
        cout << '=' << '\n';
    }else if(x>y){
        cout << '>' << '\n';
    }else if(x<y){
        cout << '<' << '\n';
    }else if(x==1){
        if(al>bl)cout << '<' << '\n';
        else cout << '>' << '\n';
    }else if(x==3){
        if(al<bl)cout << '<' << '\n';
        else cout << '>' << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}