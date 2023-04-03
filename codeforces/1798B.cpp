#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int m;
    cin >> m;
    map<int,int> mp;
    for(int i=0;i<m;i++){
        int n;
        cin >> n;
        for(int j=0;j<n;j++){
            int x;
            cin >> x;
            mp[x]=i;
        }
    }
    vector<int> v(m,-1);
    for(auto [x,y]:mp)v[y]=x;
    vector<int> ans;
    for(int i=0;i<m;i++){
        if(v[i]==-1)return void(cout << "-1\n");
        ans.emplace_back(v[i]);
    }
    for(auto x:ans)cout << x << ' ';
    cout << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}