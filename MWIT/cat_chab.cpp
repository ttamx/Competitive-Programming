#include<bits/stdc++.h>

using namespace std;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    deque<int> dq;
    for(int i=1;i<=n;i++){
        char c;
        cin >> c;
        if(c=='A')dq.push_back(i);
        else dq.push_front(i);
    }
    for(auto x:dq)cout << x << ' ';
}