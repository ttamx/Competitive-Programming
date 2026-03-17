#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int M=2e5+5;

int n,m;
int p[N];
int a[M],b[M];
vector<int> pks[N];
priority_queue<int,vector<int>,greater<int>> pq;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    for(int i=1;i<=n;i++){
        cin >> p[i];
    }
    cin >> m;
    for(int i=1;i<=m;i++){
        cin >> a[i] >> b[i];
        if(a[i]<b[i]){
            cout << -1 << "\n";
            exit(0);
        }
        pks[a[i]].emplace_back(b[i]);
    }
    int ans=1;
    for(int i=1;;i++){
        if(i<=n){
            for(auto x:pks[i]){
                pq.emplace(x);
            }
        }
        if(!pq.empty()){
            ans=max(ans,i-pq.top());
            pq.pop();
        }
        if(i>=n&&pq.empty())break;
    }
    cout << ans << "\n";
}