#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    long long sum=0;
    int mn=1e9;
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        int x;
        cin >> x;
        sum+=x;
        if(i+j==n-1)mn=min(mn,x);
    }
    cout << sum-mn << "\n";
}