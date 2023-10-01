#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m;
    cin >> n >> m;
    int num=1;
    vector<vector<int>> a(n,vector<int>(m));
    if(n>m){
        for(int i=0;i<(n+1)/2;i++){
            for(int j=0;j<m;j++){
                a[i][j]=num++;
            }
            num+=m;
        }
        num=m+1;
        for(int i=(n+1)/2;i<n;i++){
            for(int j=0;j<m;j++){
                a[i][j]=num++;
            }
            num+=m;
        }
    }else{
        for(int i=0;i<(m+1)/2;i++){
            for(int j=0;j<n;j++){
                a[j][i]=num++;
            }
            num+=n;
        }
        num=n+1;
        for(int i=(m+1)/2;i<m;i++){
            for(int j=0;j<n;j++){
                a[j][i]=num++;
            }
            num+=n;
        }
    }
    for(int i=0;i<n;i++)for(int j=0;j<m;j++)cout << a[i][j] << " \n"[j==m-1];
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}