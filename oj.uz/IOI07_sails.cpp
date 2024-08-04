#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=1e5+5;

int n;
vector<pair<int,int>> a;
ll ans;

struct Fenwick{
    int t[N];
    void update(int i,int v){
        for(;i<N;i+=i&-i)t[i]+=v;
    }
    int query(int i){
        int res=0;
        for(;i>0;i-=i&-i)res+=t[i];
        return res;
    }
}f;

int get(int x){
    int l=0,r=N-1;
    while(l<r){
        int m=(l+r+1)/2;
        if(f.query(m)>=x)l=m;
        else r=m-1;
    }
    return l;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    a.resize(n);
    for(auto &[h,k]:a)cin >> h >> k;
    sort(a.begin(),a.end());
    for(auto [h,k]:a){
        int val=f.query(h-k+1);
        int l=get(val+1),r=min(get(val),h);
        f.update(r+1,1);
        f.update(h+1,-1);
        f.update(l+1,1);
        f.update(l+k-h+r+1,-1);
    }
    for(int i=1;i<N;i++){
        int val=f.query(i);
        ans+=1LL*val*(val-1)/2;
    }
    cout << ans;
}