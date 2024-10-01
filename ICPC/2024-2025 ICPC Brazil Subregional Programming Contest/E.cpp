#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<vector<int>> a(n,vector<int>(n));
    for(auto &x:a){
        for(auto &y:x){
            cin >> y;
        }
    }
    auto check=[&](){
        for(int i=0;i<n;i++){
            for(int j=1;j<n;j++){
                if(a[i][j-1]>a[i][j]){
                    return false;
                }
            }
        }
        for(int i=1;i<n;i++){
            for(int j=0;j<n;j++){
                if(a[i-1][j]>a[i][j]){
                    return false;
                }
            }
        }
        return true;
    };
    for(int t=0;t<4;t++){
        if(check()){
            cout << t;
            exit(0);
        }
        auto b=a;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                a[i][j]=b[j][n-i-1];
            }
        }
    }
}