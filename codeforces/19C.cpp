#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    map<int,vector<int>> pos;
    map<pair<int,int>,int> lcp;
    for(int i=n-1;i>=0;i--){
        for(auto j:pos[a[i]]){
            lcp[{i,j}]=1+(lcp.count({i+1,j+1})?lcp[{i+1,j+1}]:0);
        }
        pos[a[i]].emplace_back(i);
    }
    using T = tuple<int,int,int>;
    priority_queue<T,vector<T>,greater<T>> pq;
    for(auto [e,d]:lcp){
        auto [i,j]=e;
        if(i+d>=j){
            pq.emplace(j-i,i,j);
        }
    }
    int p=0;
    while(!pq.empty()){
        auto [s,i,j]=pq.top();
        pq.pop();
        if(i<p)continue;
        p=j;
    }
    cout << n-p << "\n";
    for(int i=p;i<n;i++)cout << a[i] << " ";
    cout << "\n";
}