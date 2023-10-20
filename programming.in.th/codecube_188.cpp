#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,q;
int ans[N],l[N],r[N];
map<int,vector<int>> mp,qr;

struct fenwick{
    int t[N];
    void add(int i,int v){
        while(i<N)t[i]+=v,i+=i&-i;
    }
    int read(int i){
        int res=0;
        while(i>0)res+=t[i],i-=i&-i;
        return res;
    }
}f;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> q;
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        mp[x].emplace_back(i);
    }
    for(int i=1;i<=q;i++){
        int x;
        cin >> l[i] >> r[i] >> x;
        qr[x].emplace_back(i);
    }
    for(auto [k,v]:qr){
        auto &a=mp[k];
        for(auto i:a)f.add(i,1);
        for(auto i:v)ans[i]=f.read(r[i])-f.read(l[i]-1);
        for(auto i:a)f.add(i,-1);
    }
    for(int i=1;i<=q;i++)cout << ans[i] << '\n';
}