#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n,m,k;
    cin >> n >> m >> k;
    vector<vector<int>> add(n+2);
    for(int i=1;i<=m;i++){
        int l,r;
        cin >> l >> r;
        add[l].emplace_back(i);
        add[r+1].emplace_back(-i);
    }
    int all=0;
    map<int,int> cnt;
    map<pair<int,int>,int> cnt2;
    set<int> s;
    for(int i=1;i<=n;i++){
        for(auto x:add[i]){
            if(x>0)s.emplace(x);
            else s.erase(-x);
        }
        if(s.size()==2){
            cnt2[pair<int,int>(*s.begin(),*s.rbegin())]++;
        }else if(s.size()==1){
            cnt[*s.begin()]++;
        }else if(s.empty()){
            all++;
        }
    }
    int ans=0;
    for(auto [key,val]:cnt2){
        ans=max(ans,val+cnt[key.first]+cnt[key.second]);
    }
    pair<int,int> mx(0,0);
    for(auto [key,val]:cnt){
        mx.second=max(mx.second,val);
        if(mx.first<mx.second)swap(mx.first,mx.second);
    }
    ans=max(ans,mx.first+mx.second);
    cout << ans+all << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}