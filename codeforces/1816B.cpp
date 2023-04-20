#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<vector<int>> a(2,vector<int>(n));
    a[0][0]=2*n-1;
    a[1][n-1]=2*n;
    for(int i=1;i<n;i+=2){
        a[0][i]=i;
        a[1][i-1]=i+1;
    }
    for(int i=2;i<n;i+=2){
        a[0][i]=i+n-1;
        a[1][i-1]=i+n;
    }
    for(auto v:a){
        for(auto x:v)cout << x << ' ';
        cout << '\n';
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}