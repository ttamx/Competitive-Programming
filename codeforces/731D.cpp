#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,c;
    cin >> n >> c;
    vector<vector<int>> a(n);
    for(auto &v:a){
        int k;
        cin >> k;
        v.resize(k);
        for(auto &x:v){
            cin >> x;
            x--;
        }
    }
    vector<int> b(c+1);
    for(int i=0;i+1<n;i++){
        int j=0;
        while(j<a[i].size()&&j<a[i+1].size()&&a[i][j]==a[i+1][j])j++;
        if(j<a[i].size()&&j<a[i+1].size()){
            int u=a[i][j];
            int v=a[i+1][j];
            if(u<v){
                b[c-v]++;
                b[c-u]--;
            }else{
                b[0]++;
                b[c-u]--;
                b[c-v]++;
            }
        }else if(a[i].size()>a[i+1].size()){
            cout << -1 << "\n";
            exit(0);
        }
    }
    for(int i=1;i<=c;i++){
        b[i]+=b[i-1];
    }
    for(int i=0;i<c;i++){
        if(!b[i]){
            cout << i << "\n";
            exit(0);
        }
    }
    cout << -1 << "\n";
}