#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int w,d,h;
    cin >> w >> d >> h;
    int a,b,f,g;
    cin >> a >> b >> f >> g;
    int ans=min({a+f+abs(b-g),b+g+abs(a-f),2*w-a-f+abs(b-g),2*d-b-g+abs(a-f)});
    cout << ans+h << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}