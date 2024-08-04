#include<bits/stdc++.h>

using namespace std;

using ll = long long;

template<class T>
struct Fenwick{
    T n;
    vector<T> t;
    Fenwick(int _n):n(_n),t(n+1,T(0)){}
    void update(int i,T v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    T query(int i){
        T res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
    T query(int l,int r){
        return query(r)-query(l-1);
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    Fenwick<ll> f(n);
    for(int i=1;i<=n;i++)f.update(i,1);
    ll ans=n*3-a[0];
    f.update(a[0],-1);
    for(int i=1;i<n;i++){
        f.update(a[i],-1);
        ans+=f.query(min(a[i-1],a[i]),n);
    }
    cout << fixed << setprecision(3) << ans/2.0;
}