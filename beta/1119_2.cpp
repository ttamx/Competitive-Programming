#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),v,qs(n);
    for(auto &x:a)cin >> x,v.emplace_back(-x);
    sort(v.begin(),v.end());
    for(int i=0;i<n;i++)qs[i]=-v[i]+(i?qs[i-1]:0);
    function<int(int,int,int)> bs=[&](int l,int r,int v){
        if(l==r)return l;
        int m=(l+r)/2;
        return qs[m]>=v?bs(l,m,v):bs(m+1,r,v);
    };
    for(int i=0;i<n;i++){
        int idx=bs(0,n-1,qs[n-1]/2+1-a[i]);
        cout << (idx<upper_bound(v.begin(),v.end(),-a[i])-v.begin()-1?idx+1:bs(idx,n-1,qs[n-1]/2+1)) << '\n';
    }
}