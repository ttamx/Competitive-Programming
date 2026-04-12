#include<bits/stdc++.h>

using namespace std;

using ll = long long;
using T = tuple<int,int,int>;

const int INF=1e9;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    int m;
    cin >> m;
    vector<int> b(m);
    for(auto &x:b)cin >> x,x=a[x-1];
    sort(b.begin(),b.end());
    int ans=0;
    for(auto x:a){
        int res=INF;
        auto it=lower_bound(b.begin(),b.end(),x);
        if(it!=b.end())res=min(res,*it-x);
        if(it!=b.begin())res=min(res,x-*prev(it));
        ans=max(ans,res);
    }
    cout << ans << "\n";
}