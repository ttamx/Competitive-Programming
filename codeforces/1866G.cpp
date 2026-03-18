#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n),d(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:d){
        cin >> x;
    }
    auto check=[&](int mid){
        vector<vector<pair<int,int>>> e(n);
        for(int i=0;i<n;i++){
            if(a[i]){
                e[max(i-d[i],0)].emplace_back(i+d[i],a[i]);
            }
        }
        using P = pair<int,int>;
        priority_queue<P,vector<P>,greater<P>> pq;
        for(int i=0;i<n;i++){
            if(!pq.empty()&&pq.top().first<i){
                return false;
            }
            for(auto [x,v]:e[i])pq.emplace(x,v);
            int cur=mid;
            while(cur>0&&!pq.empty()){
                auto [x,v]=pq.top();
                pq.pop();
                if(v<=cur){
                    cur-=v;
                }else{
                    v-=cur;
                    pq.emplace(x,v);
                    break;
                }
            }
        }
        return pq.empty();
    };
    int l=0,r=1e9;
    while(l<r){
        int m=(l+r)/2;
        if(check(m))r=m;
        else l=m+1;
    }
    cout << l << "\n";
}