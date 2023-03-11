#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,k;
    cin >> n >> k;
    vector<int> p(n+1),h(n+1);
    for(int i=1;i<=n;i++)cin >> p[i];
    for(int i=1;i<=n;i++)cin >> h[i];
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.emplace(p[1],1);
    for(int i=2;i<=n;i++){
        while(!pq.empty()&&pq.top().second+k<i)pq.pop();
        int c=0;
        if(pq.top().second==h[i]){
            auto tmp=pq.top();
            pq.pop();
            while(!pq.empty()&&pq.top().second+k<i)pq.pop();
            if(!pq.empty())c=pq.top().first;
            pq.emplace(tmp);
        }else{
            c=pq.top().first;
        }
        if(c==0)continue;
        if(i==n)cout << c;
        else pq.emplace(c+p[i],i);
    }
}