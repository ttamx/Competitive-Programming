#include<bits/stdc++.h>

using namespace std;

void runcase(){
    long long n,m,k;
    cin >> n >> m >> k;
    long long mx=0;
    for(int i=0;i<m;i++){
        long long x;
        cin >> x;
        mx=max(mx,x);
    }
    if((mx-1)*k+1>n)cout << "NO\n";
    else cout << "YES\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}