#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    string a,b;
    cin >> a >> b;
    cout << (b.substr(0,n)==a?0:2)+(b.substr(m-n,n)==a?0:1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}