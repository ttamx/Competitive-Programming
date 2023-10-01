#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    long long a=0,b=0;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a+=x;
    }
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        b+=x;
    }
    if(a>b)cout << "Tsondu\n";
    else if(a<b)cout << "Tenzing\n";
    else cout << "Draw\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}