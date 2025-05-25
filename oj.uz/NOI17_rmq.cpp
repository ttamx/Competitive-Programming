#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q;
    cin >> n >> q;
    vector<tuple<int,int,int>> qr(q);
    for(auto &[l,r,v]:qr){
        cin >> l >> r >> v;
    }
    auto work=[&](const vector<tuple<int,int,int>> &a){
        vector<int> res(n);
        vector<vector<pair<int,int>>> event(n);
        for(auto [l,r,v]:a){
            event[l].emplace_back(v,r);
        }
        priority_queue<pair<int,int>> pq;
        for(int i=0;i<n;i++){
            for(auto e:event[i]){
                pq.emplace(e);
            }
            while(!pq.empty()&&pq.top().second<i){
                pq.pop();
            }
            res[i]=pq.empty()?-1:pq.top().first;
        }
        return res;
    };
    auto validate=[&](bool ok){
        if(ok)return;
        for(int i=0;i<n;i++){
            cout << -1 << " \n"[i==n-1];
        }
        exit(0);
    };
    auto req=work(qr);
    vector<int> li(n,-1),ri(n,n);
    for(auto [l,r,v]:qr){
        li[v]=max(li[v],l);
        ri[v]=min(ri[v],r);
    }
    vector<tuple<int,int,int>> need;
    for(int i=0;i<n;i++){
        if(li[i]==-1)continue;
        validate(li[i]<=ri[i]);
        need.emplace_back(li[i],ri[i],i);
    }
    auto cur=work(need);
    vector<priority_queue<pair<int,int>>> pos(n);
    for(int i=0;i<n;i++){
        if(cur[i]!=-1&&req[i]<=cur[i]){
            pos[cur[i]].emplace(req[i],i);
        }
    }
    vector<int> ans(n,-1);
    for(int i=0;i<n;i++){
        if(li[i]==-1)continue;
        validate(!pos[i].empty());
        int j=pos[i].top().second;
        pos[i].pop();
        ans[j]=i;
    }
    vector<pair<int,int>> leftover;
    for(int i=0;i<n;i++){
        if(ans[i]==-1){
            leftover.emplace_back(req[i],i);
        }
    }
    sort(leftover.begin(),leftover.end());
    for(int i=0,p=0;i<n;i++){
        if(li[i]!=-1)continue;
        auto [v,j]=leftover[p];
        validate(v<=i);
        ans[j]=i;
        p++;
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}