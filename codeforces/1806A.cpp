#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b,c,d;
    cin >> a >> b >> c >> d;
    if(d<b||d-c<b-a)return void(cout << -1 << '\n');
    int ans=d-b;
    a+=ans;
    ans+=a-c;
    cout << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}