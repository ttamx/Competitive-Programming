#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int x=0,y=0;
    bool ok=false;
    while(n--){
        char c;
        cin >> c;
        if(c=='U')x++;
        if(c=='D')x--;
        if(c=='L')y--;
        if(c=='R')y++;
        if(x==1&&y==1)ok=true;
    }
    cout << (ok?"YES":"NO") << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}