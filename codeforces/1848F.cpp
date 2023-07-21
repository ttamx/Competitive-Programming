#include<bits/stdc++.h>

using namespace std;

const int N=1e6+5;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    if(a==vector<int>(n,0))cout << 0,exit(0);
    int ans=0;
    for(int i=n/2;i>0;i/=2){
        auto b=a;
        for(int j=0;j<n;j++)b[j]=a[j]^a[(j+i)%n];
        if(b==vector<int>(n,0))continue;
        swap(a,b);
        ans|=i;
    }
    cout << ans+1;
}