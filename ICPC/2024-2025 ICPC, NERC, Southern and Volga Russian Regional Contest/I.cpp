#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,m;
    cin >> n >> m;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
        x+=x;
    }
    vector<vector<int>> pos(2*m,vector<int>(n));
    vector<int> ord(n),ans(m);
    iota(ord.begin(),ord.end(),0);
    for(int i=2*m-1;i>=0;i--){
        vector<int> nord;
        for(auto j:ord)if(a[j][i]=='0')nord.emplace_back(j);
        for(auto j:ord)if(a[j][i]=='1')nord.emplace_back(j);
        ord=move(nord);
        if(i<m)ans[i]=ord.back();
    }
    for(int i=0;i<m;i++){
        cout << ans[i]+1 << " ";
    }
}