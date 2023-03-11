#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int l,r;
    cin >> l >> r;
    int sz=0;
    while((l<<sz)<=r)sz++;
    int ans=(r>>(sz-1))-l+1;
    if(3*l<<(sz-2)<=r)ans+=(((r/3)>>(sz-2))-l+1)*(sz-1);
    cout << sz << ' ' << ans << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}