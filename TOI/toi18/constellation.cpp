#include<bits/stdc++.h>

using namespace std;

typedef long long ll;

const int N=305;

int r,c,k;
ll a[N][N][N],b[N][N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> r >> c >> k;
    for(int i=1;i<=r;i++){
        for(int j=1;j<=c;j++){
            char x;
            cin >> x;
            for(int l=1;l<=300;l++){
                if(j+l-i<=c)a[l][0][j+l-i]++;
                if(j+k+1<=c)a[l][0][j+k+1]--;
                if(j-l+i>=1)b[l][0][j-l+i]++;
            }
        }
    }
}