#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n==3){
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    int a=-1,b=1;
    if(n&1)a=-n/2,b=n/2-1;
    for(int i=0;i<n;i++)cout << (i&1?a:b) << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}