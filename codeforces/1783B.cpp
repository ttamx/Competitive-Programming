#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    int l=1,r=n*n;
    vector<int> a(n*n);
    for(int i=0;i<n*n;i++){
        if(i&1)a[i]=r--;
        else a[i]=l++;
    }
    vector<vector<int>> ans(n,vector<int>(n));
    int idx=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if(i&1)ans[i][n-j-1]=a[idx++];
            else ans[i][j]=a[idx++];
        }
    }
    for(auto v:ans){
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