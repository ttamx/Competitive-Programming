#include<bits/stdc++.h>

using namespace std;

const int N=150005;

int n;
int a[N][3];
pair<int,int> b[3][N];
int id[3];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=0;i<n;i++){
        for(int j=0;j<3;j++){
            cin >> a[i][j];
            b[j][i]={a[i][j],i};
        }
    }
    for(int i=0;i<3;i++)sort(b[i],b[i]+n,greater<pair<int,int>>());
    while(id[0]<n&&id[1]<n&&id[2]<n){
        bool ok=true;
        for(int i=0,j=1,k=2;i<3;i++,j++,k++){
            if(j==3)j=0;
            if(k==3)k=0;
            int x=b[i][id[i]].second,y=b[j][id[j]].second,z=b[k][id[k]].second;
            if(a[x][j]>=a[y][j]||a[x][k]>=a[z][k]){
                id[i]++;
                ok=false;
                break;
            }
        }
        if(ok)cout << b[0][id[0]].first+b[1][id[1]].first+b[2][id[2]].first,exit(0);
    }
    cout << -1;
}