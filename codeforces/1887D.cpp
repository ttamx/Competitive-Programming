#include "template.hpp"
#include "data-structure/dsu.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    int q;
    cin >> q;
    vector<priority_queue<pair<int,int>>> pq(n);
    vector<bool> ans(q);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        pq[r].emplace(l,i);
    }
    DSU dsu(n);
    vector<int> b(n);
    for(int i=0;i<n;i++){
        b[a[i]]=i;
    }
    vector<int> l(n);
    for(int i=0;i<n;i++){
        l[i]=i;
    }
    set<int> s;
    s.emplace(n);
    auto work=[&](int u){
        u=dsu.find(u);
        while(!pq[u].empty()){
            auto [p,i]=pq[u].top();
            p=dsu.find(p);
            if(p==u){
                pq[u].pop();
                continue;
            }
            if(*s.lower_bound(p)<l[u]){
                break;
            }
            ans[i]=true;
            pq[u].pop();
        }
    };
    auto merge=[&](int u,int v){
        u=dsu.find(u),v=dsu.find(v);
        assert(u!=v);
        if(pq[u].size()<pq[v].size()){
            swap(pq[u],pq[v]);
        }
        while(!pq[v].empty()){
            pq[u].emplace(pq[v].top());
            pq[v].pop();
        }
        l[u]=min(l[u],l[v]);
        dsu.merge(u,v);
    };
    for(int i=n-1;i>=0;i--){
        int p=b[i];
        s.emplace(p);
        if(p>0&&a[p-1]>i){
            merge(p-1,p);
        }
        if(p+1<n&&a[p+1]>i){
            merge(p,p+1);
        }
        work(p);
    }
    for(auto x:ans){
        cout << (x?"Yes":"No") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}