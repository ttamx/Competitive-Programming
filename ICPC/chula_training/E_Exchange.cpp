#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,a,b;
    cin >> n >> a >> b;
    cout << (a>b?1:((n-1)/a+1)) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}