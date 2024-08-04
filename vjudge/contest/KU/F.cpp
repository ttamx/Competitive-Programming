#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    while(true){
        int n;
        cin >> n;
        if(n==-1)break;
        vector<vector<int>> a(n,vector<int>(n));
        for(auto &v:a)for(auto &x:v)cin >> x;
        vector<bool> ok(n);
        for(int i=0;i<n;i++)for(int j=0;j<i;j++)for(int k=0;k<j;k++){
            if(a[i][j]&&a[i][k]&&a[j][k])ok[i]=ok[j]=ok[k]=true;
        }
        for(int i=0;i<n;i++)if(!ok[i])cout << i << " ";
        cout << "\n";
    }
}