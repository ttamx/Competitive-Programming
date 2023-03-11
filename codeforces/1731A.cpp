#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    long long ans=1;
    for(int i=0;i<n;i++){
        long long x;
        cin >> x;
        ans*=x;
    }
    cout << (ans+n-1)*2022 << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}