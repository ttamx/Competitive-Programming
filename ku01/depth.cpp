#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<int> d(n+1),l(n+1);
    vector<queue<int>> v(n);
    vector<int> b;
    for(int i=1;i<=n;i++){
        int x,y;
        cin >> x >> y;
        d[i]=d[i-1]+x;
        l[i]=l[i-1]+y;
        if(x>0)b.push_back(i);
        else v[d[i]+1].push(l[i-1]);
    }
    v[1].push(l[n]);
    vector<pair<int,int>> ans;
    for(auto i:b){
        ans.push_back({v[d[i]].front()-l[i-1],d[i]});
        v[d[i]].pop();
    }
    sort(ans.begin(),ans.end());
    ans.push_back({1e9+10,0});
    for(int i=ans.size()-2;i>=0;i--)ans[i].second=max(ans[i].second,ans[i+1].second);
    ans.erase(unique(ans.begin(),ans.end()),ans.end());
    while(q--){
        int x;
        cin >> x;
        cout << lower_bound(ans.begin(),ans.end(),make_pair(x,0))->second << '\n';
    }
}