#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &v:a)for(auto &x:v)cin >> x;
    vector<int> b(n,(1<<30)-1);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(i!=j)b[i]&=a[i][j];
    for(int i=0;i<n;i++)for(int j=0;j<n;j++)if(i!=j&&(b[i]|b[j])!=a[i][j])return void(cout << "NO\n");
    cout << "YES\n";
    for(auto x:b)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}