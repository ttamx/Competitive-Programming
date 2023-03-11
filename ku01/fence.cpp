#include<bits/stdc++.h>

using namespace std;

const int N=2e5+5;

struct coor{
    int x1=350,x2=1,y1=350,y2=1;
    void expand(coor o){
        x1=min(x1,o.x1);
        x2=max(x2,o.x2);
        y1=min(y1,o.y1);
        y2=max(y2,o.y2);
    }
    int calc(){
        return max(0,(x2-x1+y2-y1+2)*2);
    }
}a[N],dp[N];

coor makecoor(int a,int b,int c,int d){
    coor ret;
    ret.x1=a,ret.x2=b,ret.y1=c,ret.y2=d;
    return ret;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int h,w,q;
    cin >> h >> w >> q;
    int mx=0;
    for(int i=1;i<=h;i++)for(int j=1;j<=w;j++){
        int v;
        cin >> v;
        a[v].expand(makecoor(i,i,j,j));
        mx=max(mx,v);
    }
    dp[mx]=a[mx];
    for(int i=mx-1;i>=0;i--){
        dp[i]=a[i];
        dp[i].expand(dp[i+1]);
    }
    while(q--){
        int x,y;
        cin >> x >> y;
        if(x==1)cout << a[y].calc() << '\n';
        else cout << dp[y].calc() << '\n';
    }
}