#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    if(n==3){
        cout << -1 << '\n';
    }else if(n&1){
        for(int i=n;i>n/2+1;--i)cout << i << ' ';
        for(int i=1;i<=n/2+1;++i)cout << i << ' ';
        cout << '\n';
    }else{
        for(int i=n;i>0;--i)cout << i << ' ';
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}