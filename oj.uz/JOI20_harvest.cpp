#include<bits/stdc++.h>

using namespace std;

using ll = long long;

const int N=2e5+5;

int n,m,q;
ll l,c;
ll a[N],b[N];
vector<pair<ll,int>> qr[N];
vector<pair<ll,int>> event;
int par[N*2];
ll dist[N*2];

struct Fenwick{

};

void sack(){

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n >> m >> l >> c;
    for(int i=1;i<=n;i++){
        cin >> a[i];
    }
    for(int i=1;i<=n;i++){
        cin >> b[i];
    }
    cin >> q;
    for(int i=1;i<=q;i++){
        int x;
        ll t;
        cin >> x >> t;
        qr[x].emplace_back(t,i);
    }
    for(int i=1;i<=n;i++){
        event.emplace_back(a[i],i);
        event.emplace_back(a[i]+l,i);
    }
    for(int i=1;i<=m;i++){
        event.emplace_back(b[i],i+n);
        event.emplace_back(b[i]+l,i+n);
    }
    sort(event.begin(),event.end());
    deque<pair<ll,int>> dq;
    for(auto [t,i]:event){
        if(i<=n){
            dq.emplace_back(t,i);
            while(dq.size()>=2&&t-dq[1].first>=c){
                dq.pop_front();
            }
            if(t-dq[0].first>=c){
                par[i]=dq[0].second;
                dist[i]=t-dq[0].first;
            }
        }else{
            if(!dq.empty()){
                par[i]=dq.back().second;
                dist[i]=t-dq.back().first;
            }
        }
    }
    for(int i=1;i<=n+m;i++){
        cerr << i << " -> " << par[i] << " : " << dist[i] << "\n";
    }
    // to lazy to implement ;-;
}