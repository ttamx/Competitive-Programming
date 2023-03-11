#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

void runcase(){
    int n;
    cin >> n;
    if(n&1){
        for(int i=1;i<n/2;i++){
            cout << n-i+3 << ' ' << n+i+3 << ' ';
        }
        cout << n+3 << ' ' << n+n/2+4 << ' ' << n+n/2+7;
    }else{
        for(int i=1;i<=n/2;i++){
            cout << n-i << ' ' << n+i << ' ';
        }
    }
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}