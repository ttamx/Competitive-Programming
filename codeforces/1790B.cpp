#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,s,r;
    cin >> n >> s >> r;
    int mx=s-r;
    r-=n-1;
    cout << mx-- << ' ';
    for(int i=1;i<n;i++){
        cout << min(mx,r)+1 << ' ';
        r-=min(mx,r);
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}