#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int m;
    string n;
    cin >> m >> n;
    if(n.size()>m||m==1)return void(cout << "YES\n");
    if(n.size()<m)return void(cout << "NO\n");
    for(int i=1;i<m;i++)if(n[i]=='1')return void(cout << "YES\n");
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}