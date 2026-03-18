#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int m;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    ll tot=0;
    vector<pair<int,int>> ans;
    auto work=[&](int i,int d){
        assert(a[i]>=d);
        tot+=d;
        ans.emplace_back(i,d);
        a[i]-=d;
        if(i>0)a[i-1]=max(a[i-1]-d,0);
        if(i+1<n)a[i+1]=max(a[i+1]-d,0);
    };
    for(int i=1;i+1<n;i++){
        int d=min({a[i-1]+a[i+1]-a[i],a[i-1],a[i],a[i+1]});
        if(d>0)work(i,d);
    }
    for(int i=0;i<n;i++){
        if(a[i]==0)continue;
        if((i==0||a[i-1]<a[i])&&(i==n-1||a[i+1]<a[i])){
            work(i,a[i]);
        }
    }
    for(int i=0;i<n;i++){
        if(a[i]==0)continue;
        work(i,a[i]);
    }
    cout << tot << "\n";
    if(m){
        cout << ans.size() << "\n";
        for(auto [i,d]:ans)cout << i+1 << " " << d << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t >> m;
    while(t--)runcase();
}