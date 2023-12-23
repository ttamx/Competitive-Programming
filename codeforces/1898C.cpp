#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    int d=n+m-2;
    if((k+d)%2==1||k<d)return void(cout << "NO\n");
    cout << "YES\n";
    for(int j=0;j<n;j++)for(int i=0;i<m-1;i++)cout << ((i+n)%2==0?'R':'B') << " \n"[i==m-2];
    for(int j=0;j<n-1;j++)for(int i=0;i<m;i++)cout << ((j+i+(j==n-2&&i==m-1))%2==1?'R':'B') << " \n"[i==m-1];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}