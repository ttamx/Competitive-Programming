#include<bits/stdc++.h>

using namespace std;

using ll = long long;

void runcase(){
    int n,k,m;
    cin >> n >> k >> m;
    vector<vector<pair<int,int>>> bel(n);
    vector<set<pair<int,int>>> a(m);
    for(int i=0;i<m;i++){
        int len;
        cin >> len;
        for(int j=0;j<len;j++){
            int x;
            cin >> x;
            x--;
            bel[x].emplace_back(i,j);
            a[i].emplace(j,x);
        }
    }
    vector<int> dist(n,-1);
    queue<int> q;
    dist[0]=0;
    q.emplace(0);
    while(!q.empty()){
        int u=q.front();
        q.pop();
        for(auto [i,j]:bel[u]){
            auto it=a[i].lower_bound(make_pair(j,0));
            while(it!=a[i].end()&&it->first<=j+k){
                int v=it->second;
                if(dist[v]==-1){
                    dist[v]=dist[u]+1;
                    q.emplace(v);
                }
                it=a[i].erase(it);
            }
        }
    }
    ll ans=0;
    for(int i=0;i<n;i++){
        ans+=ll(dist[i])*ll(i+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cout << fixed << setprecision(15);
    int t(1);
    cin >> t;
    for(int i=1;i<=t;i++){
        cout << "Case #" << i << ": ";
        runcase();
    }
}