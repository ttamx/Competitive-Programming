#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int a[4];
    for(int i=0;i<4;++i)cin >> a[i];
    sort(a,a+4);
    cout << a[0]*a[2] << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}