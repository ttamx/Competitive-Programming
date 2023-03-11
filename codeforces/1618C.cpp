#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<long long> a(n);
    for(auto &x:a)cin >> x;
    long long d[2]={};
    for(int i=0;i<n;i++)d[i&1]=gcd(d[i&1],a[i]);
    bool ok[2]={true,true};
    for(int i=0;i<n;i++)if(a[i]%d[i&1^1]==0)ok[i&1^1]=false;
    if(ok[0])cout << d[0];
    else if(ok[1])cout << d[1];
    else cout << 0;
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}