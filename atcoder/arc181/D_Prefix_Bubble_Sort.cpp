#include<bits/stdc++.h>

using namespace std;

using ll = long long;

struct Fenwick{
    int n;
    vector<int> t;
    Fenwick(int _n):n(_n),t(n+1,0){}
    void update(int x,int v){
        for(int i=x;i<=n;i+=i&-i)t[i]+=v;
    }
    int query(int x){
        int res=0;
        for(int i=x;i>0;i-=i&-i)res+=t[i];
        return res;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
    }
    Fenwick f(n);
    vector<int> b(n);
    ll ans=0;
    for(int i=0;i<n;i++){
        b[i]=i-f.query(a[i]);
        ans+=b[i];
        f.update(a[i],1);
    }
    priority_queue<int,vector<int>,greater<int>> pq;
    int lz=0;
    int m;
    cin >> m;
    int p=0;
    for(int i=0;i<m;i++){
        int x;
        cin >> x;
        while(p<x){
            pq.emplace(b[p]+lz);
            p++;
        }
        lz++;
        while(!pq.empty()&&pq.top()<lz){
            pq.pop();
        }
        ans-=pq.size();
        cout << ans << "\n";
    }
}