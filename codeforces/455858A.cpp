#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    for(int i=1;i<=n;i++)cout << 2*i << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}