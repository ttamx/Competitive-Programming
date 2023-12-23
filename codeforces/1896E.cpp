#include<bits/stdc++.h>

using namespace std;

template<class T>
struct fenwick{
    int n;
    vector<T> t;
    fenwick(){}
    fenwick(int _n){
        n=_n;
        t.assign(n+1,0);
    }
    void update(int i,T v){
        for(;i<=n;i+=i&-i)t[i]+=v;
    }
    void update(int l,int r,T v){
        update(l,v);
        update(r+1,-v);
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

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n+2),ans(n+2);
    vector<vector<int>> add(2*n+2);
    vector<vector<pair<int,int>>> vec(2*n+2);
    vector<pair<int,int>> v;
    for(int i=1;i<=n;i++){
        cin >> a[i];
        int l=i,r=a[i];
        if(l<=r){
            v.emplace_back(l,r);
            v.emplace_back(l+n,r+n);
        }else{
            r+=n;
            v.emplace_back(l,r);
        }
        ans[a[i]]=r-l;
        vec[r].emplace_back(l,a[i]);
    }
    fenwick<int> f(2*n+5);
    for(auto [l,r]:v)add[r].emplace_back(l);
    for(int i=0;i<=2*n;i++){
        for(auto x:add[i])f.update(x,1);
        for(auto [x,j]:vec[i])ans[j]-=f.query(i)-f.query(x);
    }
    for(int i=1;i<=n;i++)cout << ans[i] << " \n"[i==n];
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}