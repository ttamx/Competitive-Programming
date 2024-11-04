#include "template.hpp"
#include "modular-arithmetic/montgomery-modint.hpp"

using mint = mint998;

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<int> p(n),deg(n);
    ll tot=0;
    for(auto &x:p){
        cin >> x;
        x--;
        if(x!=-1){
            deg[x]++;
        }
    }
    for(auto &x:a){
        cin >> x;
        tot+=x;
    }
    ll cur=0,sum=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    for(int i=0;i<n;i++){
        if(deg[i]==0){
            pq.emplace(a[i],i);
        }
    }
    while(!pq.empty()){
        auto [val,u]=pq.top();
        pq.pop();
        cur+=val;
        sum+=cur;
        int v=p[u];
        if(v!=-1){
            deg[v]--;
            if(deg[v]==0){
                pq.emplace(a[v],v);
            }
        }
    }
    cout << mint(sum)/mint(tot) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}