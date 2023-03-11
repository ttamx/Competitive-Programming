#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    sort(a.begin(),a.end());
    deque<int> dq;
    for(auto &x:a)dq.emplace_back(x);
    int ans=0;
    while(!dq.empty()){
        ans+=dq.back();
        dq.pop_back();
        for(int i=0;i<3&&!dq.empty();++i){
            ans+=dq.front();
            dq.pop_front();
        }
        if(!dq.empty()){
            dq.pop_back();
        }
    }
    cout << ans;
}
