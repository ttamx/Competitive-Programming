#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,k;
    cin >> n >> k; 
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int cnt=1;
    for(auto x:a)if(x==cnt)cnt++;
    cout << (n-cnt+k)/k << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}