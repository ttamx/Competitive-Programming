#include<bits/stdc++.h>

using namespace std;

const int N=1e5+5;

int n,ans;
int a[N];
map<int,vector<int>> mp;
vector<int> d;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;++i){
        cin >> a[i];
        if(mp[a[i]].size()==0)mp[a[i]].emplace_back(0);
        mp[a[i]].emplace_back(i);
    }
    a[0]=a[n+1]=2e9;
    for(auto [h,v]:mp){
        mp[a[i]].emplace_back(n+1);
        for(int i=1;i<v.size()-1;++i){
            if(h==v[i-1]||h==v[i+1])continue;
            int mn=min(max(h,a[i-1]),max(h,a[i+1]));
            ans+=mn-h;
            cout << i << ": " << h << "->" << mn << '\n';
            a[i]=mn;
            if(a[i]!=a[i+1]&&a[i]!=a[i-1])d.emplace_back(i);
        }
    }
    for(auto i:d)cout << i << '\t';
    cout << ans;
}
