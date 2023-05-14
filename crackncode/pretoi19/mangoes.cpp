#include<bits/stdc++.h>

using namespace std;

const int N=5005;
const int M=1e5+5;

int n,m,r,c;
int qs[N][N];
tuple<int,int,int> a[M];

int calc(int x,int y,int z,int w){
    x=max(0,x-1);
    y=max(0,y-1);
    z=min(r,z);
    w=min(c,w);
    return qs[z][w]-qs[z][y]-qs[x][w]+qs[x][y];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> r >> c;
    for(int i=1;i<=n;i++){
        auto &[x,y,z]=a[i];
        cin >> x >> y >> z;
    }
    for(int i=1;i<=m;i++){
        int x,y;
        cin >> x >> y;
        qs[x][y]++;
    }
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            qs[i][j]+=qs[i-1][j]+qs[i][j-1]-qs[i-1][j-1];
        }
    }
    int d=0;
    for(int i=1;i<=n;i++){
        auto &[x,y,z]=a[i];
        while(calc(x-d,y-d,x+d,y+d)<z)d++;
    }
    cout << d;
}