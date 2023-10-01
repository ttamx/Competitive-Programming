#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a,b,c,d,e,f;
    cin >> a >> b >> c >> d >> e >> f;
    int ans=0;
    ans=max(ans,min(max(0,a-c),max(0,a-e))+min(max(0,b-d),max(0,b-f)));
    ans=max(ans,min(max(0,a-c),max(0,a-e))+min(max(0,d-b),max(0,f-b)));
    ans=max(ans,min(max(0,c-a),max(0,e-a))+min(max(0,b-d),max(0,b-f)));
    ans=max(ans,min(max(0,c-a),max(0,e-a))+min(max(0,d-b),max(0,f-b)));
    cout << ans+1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}