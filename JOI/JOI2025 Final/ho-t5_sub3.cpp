#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;
const int M=2e5+5;

int n,m;
int p[N];
int a[M],b[M];
int aux[M];
int cut;
vector<pair<int,int>> pks;
priority_queue<int> pq;

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
        cut=max(cut,b[i]);
    }
    for(int i=1;i<=m;i++){
        pks.emplace_back(a[i]-cut,cut-b[i]);
    }
    sort(pks.begin(),pks.end());
    int cur=0;
    int ans=0;
    for(int t=1;;t++){
        ans=max(ans,t);
        while(cur<m&&pks[cur].first<=t){
            pq.emplace(pks[cur].second);
            cur++;
        }
        if(!pq.empty()){
            ans=max(ans,t+pq.top());
            pq.pop();
        }
        if(cur>=m&&pq.empty()){
            break;
        }
    }
    cout << ans << "\n";
}