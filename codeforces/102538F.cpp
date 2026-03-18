#include<bits/stdc++.h>

using namespace std;

using ll = long long;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,a,b;
    cin >> n >> a >> b;
    ll bal=1;
    priority_queue<int> pq;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        bal+=x/b+1;
        int v=(x%b)/a+2;
        pq.emplace(v);
        bal-=v;
        while(bal<0){
            bal+=pq.top();
            pq.pop();
        }
    }
    cout << pq.size() << "\n";
}