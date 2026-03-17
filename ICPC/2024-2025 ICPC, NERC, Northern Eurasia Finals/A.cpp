#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> b(n),ib(n+1);
    iota(b.begin(),b.end(),1);
    for(int i=0;i<n;i++){
        ib[b[i]]=i;
    }
    vector<pair<int,int>> ans;
    auto work=[&](int i,int j){
        ans.emplace_back(b[j],b[i]);
        swap(b[i],b[j]);
        swap(ib[b[i]],ib[b[j]]);
    };
    for(int i=n-1;i>=0;i--){
        int j=ib[a[i]];
        for(;j>0;j--)work(j-1,j);
        for(;j<i;j++)work(j,j+1);
    }
    cout << ans.size() << "\n";
    for(auto [x,y]:ans){
        cout << x << " " << y << "\n";
    }
}