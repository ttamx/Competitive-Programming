#include "template.hpp"
#include "data-structure/segment-tree/dynamic-segment-tree.hpp"
#include "group/monoid-action/max-add.hpp"

struct Event{
    int t,l,r,v;
    Event(int _t,int _l,int _r,int _v):t(_t),l(_l),r(_r),v(_v){}
    bool operator<(const Event &e)const{
        return t>e.t;
    }
};

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    int L=1e9;
    DynamicSegmentTree<MaxAddAction<int>> s(0,L+1,[](int,int){return 0;});
    priority_queue<Event> pq;
    vector<int> b;
    b.emplace_back(0);
    for(int i=0;i<n;i++){
        int l,r;
        cin >> l >> r;
        b.emplace_back(l+1);
        b.emplace_back(l);
        b.emplace_back(r);
        b.emplace_back(r-1);
        pq.emplace(l+1,r+1,L,1);
        pq.emplace(r,r+1,L,-1);
        if(r-l>1){
            s.update(l+1,r-1,1);
            pq.emplace(l,l+1,r-1,-1);
        }
    }
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int ans=0,l=0,r=1;
    for(auto x:b){
        while(pq.size()&&pq.top().t<=x){
            auto e=pq.top();
            pq.pop();
            s.update(e.l,e.r,e.v);
        }
        int mx=s.query(x+1,L);
        if(mx>ans){
            ans=mx;
            l=x;
            r=s.findfirst(x+1,L,[&](int v){return v>=mx;});
        }
    }
    cout << l << " " << r << "\n";
}