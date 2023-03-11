#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    string ans="NO";
    for(int i=0;i<4;i++){
        if(a<b&&a<c&&b<d&&c<d)ans="YES";
        swap(a,b);
        swap(c,a);
        swap(d,c);
    }
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}