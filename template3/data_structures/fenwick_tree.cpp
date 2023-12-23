#include<bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<ll,ll> p2;

template<class T>
struct Fenwick{
    int n;
    vector<T> t;
    Fenwick(int _n=0){
        init(_n);
    }
    void init(int _n){
        n=_n;
        t.assign(n+1,T{});
    }
    void update(int x,const T &v){
        for(int i=x;i<=n;i++)t[i]=t[i]+v;
    }
    void update(int l,int r,const T &v){
        update(l,v);
        update(r+1,-v);
    }
    T query(int x){
        T res{};
        for(int i=x;i>0;i-=i&-i)res=res+t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
    int find(const T &k){
        int x=0;
        T cur{};
        for(int i=1<<__lg(n);i>0;i>>=1)if(x+i<=n&&cur+t[x+i]<=k)x+=i,cur=cur+t[i];
        return x;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    
}