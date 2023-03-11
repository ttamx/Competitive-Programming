#include<bits/stdc++.h>

using namespace std;

const int N=1e4+5;

struct fenwick{
    int f[N][N];
    void add(int x,int y,int v){
        for(int i=x;i<N;i+=i&-i)for(int j=y;j<N;j+=j&-j)f[i][j]+=v;
    }
    int read(int x,int y){
        int ret=0;
        for(int i=x;i;i-=i&-i)for(int j=y;j;j-=j&-j)ret+=f[i][j];
        return ret;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    while(n--){
        int p,h;
        cin >> p >> h;
        cout << f.read(p-h+5001,N-1)-f.read(p-h+5001,p+h-1) << '\n';
        f.add(p-h+5001,p+h,1);
    }
}