#include<bits/stdc++.h>

using namespace std;

int n,k;
deque<pair<int,int>> dq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> k;
    dq.emplace_back(0,1-k);
    for(int i=1;i<=n;i++){
        int x;
        cin >> x;
        while(dq.front().second+k<i)dq.pop_front();
        x+=dq.front().first;
        while(dq.back().first>=x)dq.pop_back();
        dq.emplace_back(x,i);
    }
    cout << dq.back().first;
}