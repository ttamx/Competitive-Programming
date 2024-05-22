#include<bits/stdc++.h>

using namespace std;

const int N=15005;

int n,m;
int a[N];
int b[N];
int sum=0;
priority_queue<pair<int,int>> pq;
vector<vector<int>> ans;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> a[i],sum+=a[i];
        pq.emplace(a[i],i);
    }
    cin >> m;
    assert(m==1);
    for(int i=1;i<=m;i++)cin >> b[i];
    while(pq.size()>=b[1]){
        vector<pair<int,int>> res;
        vector<int> tmp;
        for(int i=0;i<b[1];i++){
            if(pq.top().first>1){
                res.emplace_back(pq.top().first-1,pq.top().second);
            }
            tmp.emplace_back(pq.top().second);
            pq.pop();
        }
        for(auto x:res)pq.emplace(x);
        ans.emplace_back(tmp);
    }
    if(!pq.empty())cout << -1,exit(0);
    cout << ans.size() << '\n';
    for(auto v:ans){
        cout << v.size() << ' ';
        for(auto x:v)cout << x << ' ';
        cout << '\n';
    }
}