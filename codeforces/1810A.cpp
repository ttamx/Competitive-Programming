#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    bool ok=false;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        if(x<=i+1)ok=true;
    }
    if(ok)cout << "YES\n";
    else cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}