#include<bits/stdc++.h>

using namespace std;

const int N=505;

int a[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m,k;
    cin >> n >> m >> k;
    for(int i=0;i<k;i++){
        int x,y;
        cin >> x >> y;
        a[x][y]++;
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(a[i][j]){
                cout << "B";
            }else{
                int v=0;
                for(int ii=-1;ii<=1;ii++){
                    for(int jj=-1;jj<=1;jj++){
                        v+=a[i+ii][j+jj];
                    }
                }
                cout << v;
            }
            cout << " \n"[j==m];
        }
    }
}