#include<bits/stdc++.h>

using namespace std;

void solve(){
    int n,m;
    cin >> n >> m;
    if(n==1){
        cout << "YES\n";
        for(int i=1;i<=m;i++){
            cout << i << " \n"[i==m];
        }
        return;
    }
    if(m==1){
        cout << "YES\n";
        for(int i=1;i<=n;i++){
            cout << i << "\n";
        }
        return;
    }
    if(n==m){
        cout << "YES\n";
        vector<int> a(n);
        iota(a.begin(),a.end(),1);
        for(int i=0;i<n;i++){
            for(auto x:a){
                cout << x+i*n << " ";
            }
            cout << "\n";
            next_permutation(a.begin(),a.end());
        }
        return;
    }
    if((n*m)%2==1){
        cout << "NO\n";
        return;
    }
    vector<vector<int>> a(n,vector<int>(m));
    int num=1;
    if(m%2==0){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                a[i][j]=num++;
            }
        }
    }else{
        for(int j=0;j<m;j++){
            for(int i=0;i<n;i++){
                a[i][j]=num++;
            }
        }
    }
    cout << "YES\n";
    for(auto &v:a){
        for(auto x:v){
            cout << x << " ";
        }
        cout << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)solve();
}