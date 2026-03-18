#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto vals=a;
    sort(vals.begin(),vals.end());
    vals.erase(unique(vals.begin(),vals.end()),vals.end());
    int k=vals.size();
    vector<int> cnt(k);
    for(auto &x:a){
        x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
        cnt[x]++;
    }
    vector<vector<int>> bad(k);
    for(int i=0;i<m;i++){
        int x,y;
        cin >> x >> y;
        x=lower_bound(vals.begin(),vals.end(),x)-vals.begin();
        y=lower_bound(vals.begin(),vals.end(),y)-vals.begin();
        bad[x].emplace_back(y);
        bad[y].emplace_back(x);
    }
    vector<int> ord(k);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return cnt[i]<cnt[j];
    });
    vector<set<int>> s(n+1);
    vector<bool> mark(k+1);
    ll ans=0;
    for(auto j:ord){
        for(auto x:bad[j]){
            if(mark[x]){
                s[cnt[x]].erase(x);
            }
        }
        for(int i=0;i<=cnt[j];i++){
            if(!s[i].empty()){
                ans=max(ans,1LL*(i+cnt[j])*(vals[j]+vals[*s[i].rbegin()]));
            }
        }
        for(auto x:bad[j]){
            if(mark[x]){
                s[cnt[x]].emplace(x);
            }
        }
        s[cnt[j]].emplace(j);
        mark[j]=true;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}