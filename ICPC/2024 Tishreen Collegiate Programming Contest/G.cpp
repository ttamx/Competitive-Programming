#include<bits/stdc++.h>

using namespace std;

const int N=105;

__int128_t c[N][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    for(int i=1;i<=100;i++){
        c[i][0]=c[i][i]=1;
        for(int j=1;j<i;j++){
            c[i][j]=c[i-1][j-1]+c[i-1][j];
        }
        __int128_t g=0;
        for(int j=1;j*2<=i;j++){
            __int128_t v=c[i][j];
            if(j*2<i){
                v*=2;
            }
            g=gcd(g,v);
        }
        cout << i << " : " << (long long)g << "\n";
        // cout << "MAX : " << c[i][i/2] << "\n";
    }
}