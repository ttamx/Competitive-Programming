#include<bits/stdc++.h>

using namespace std;

const int N=5e5+5;

int n,m;
int qs[2][N];

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        qs[x<0][i]=abs(x);
        qs[0][i]+=qs[0][i-1];
        qs[1][i]+=qs[1][i-1];
    }
    while(m--){
        int x,h;
        cin >> x >> h;
        cout << qs[0][lower_bound(qs[1]+x,qs[1]+n+1,h+qs[1][x])-qs[1]-1]-qs[0][x] << '\n';
    }
}