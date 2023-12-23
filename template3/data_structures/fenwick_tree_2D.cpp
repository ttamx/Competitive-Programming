#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

template<class T>
struct Fenwick2D{
    int n,m;
    vector<vector<T>> t;
    Fenwick2D(int _n=0,int _m=0){
        init(_n,_m);
    }
    void init(int _n,int _m){
        n=_n,m=_m;
        t.assign(n+1,vector<T>(m+1,T{}));
    }
    void update(int x,int y,const T &v){
        for(int i=x;i<=n;i+=i&-i)for(int j=y;j<=m;j+=j&-j)t[i][j]=t[i][j]+v;
    }
    void update(int x1,int y1,int x2,int y2,const T &v){
        update(x1,y1,v);
        update(x1,y2+1,-v);
        update(x2+1,y1,-v);
        update(x2+1,y2+1,v);
    }
    T query(int x,int y){
        T res{};
        for(int i=x;i>0;i-=i&-i)for(int j=y;j>0;j-=j&-j)res=res+t[i][j];
        return res;
    }
    T query(int x1,int y1,int x2,int y2){
        return query(x2,y2)-query(x2,y1-1)-query(x1-1,y2)+query(x1-1,y1-1);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}