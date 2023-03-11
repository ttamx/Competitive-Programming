#include<bits/stdc++.h>

using namespace std;

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    bool one=false,ok=true;
    for(auto &x:a)cin >> x,one|=(x==1);
    for(int i=1;i<n;i++)ok&=(a[i]==a[i-1]);
    if(ok)return void(cout << 0 << '\n');
    if(one)return void(cout << -1 << '\n');
    priority_queue<pair<int,int>> pq;
    for(int i=0;i<n;i++)pq.emplace(a[i],i+1);
    vector<pair<int,int>> ans;
    while(pq.top().first>2&&ans.size()<=30*n){
        auto [val,idx]=pq.top();
        pq.pop();
        vector<int> res;
        res.emplace_back(idx);
        while(!pq.empty()&&pq.top().first==val){
            res.emplace_back(pq.top().second);
            pq.pop();
        }
        if(pq.empty())break;
        auto [val2,idx2]=pq.top();
        for(auto idx1:res){
            pq.emplace(ceil(1.0*val/val2),idx1);
            ans.emplace_back(idx1,idx2);
        }
    }
    if(ans.size()>30*n)return void(cout << -1 << '\n');
    cout << ans.size() << '\n';
    for(auto [x,y]:ans)cout << x << ' ' << y << '\n';
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}