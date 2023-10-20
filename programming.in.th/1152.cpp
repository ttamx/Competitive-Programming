#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    vector<priority_queue<int>> a(2*n);
    for(int i=0;i<n;i++)for(int j=0;j<n;j++){
        int x;
        cin >> x;
        a[i+j].push(x);
    }
    multiset<int> ms;
    for(int i=1;i<=2*n-2;i++){
        ms.insert(a[i].top());
        a[i].pop();
        while(!a[i].empty()&&a[i].top()>=*ms.begin()){
            ms.erase(ms.begin());
            ms.insert(a[i].top());
            a[i].pop();
        }
    }
    int ans=0;
    for(auto x:ms)ans+=x;
    cout << ans;
}