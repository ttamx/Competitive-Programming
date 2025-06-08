#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    int ans,pre,suf,sum;
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        return Info{max({l.ans,r.ans,l.suf+r.pre}),max(l.pre,l.sum+r.pre),max(r.suf,r.sum+l.suf),l.sum+r.sum};
    }
    static Info unit(){return Info{0,-INF,-INF,0};}
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<vector<pair<int,int>>> event(n);
    for(int i=0;i<n;i++)event[a[i]].emplace_back(0,i);
    for(int i=0;i<q;i++){
        int x,v;
        cin >> x >> v;
        x--,v--;
        event[a[x]].emplace_back(i,~x);
        event[v].emplace_back(i,x);
        a[x]=v;
    }
    SegmentTree<Monoid> seg(n);
    vector<vector<int>> upd(q+1);
    auto work=[&](int l,int r,int v){
        if(v<=0)return;
        upd[l].emplace_back(v);
        upd[r].emplace_back(~v);
    };
    for(int v=0;v<n;v++){
        int last=0;
        for(auto [t,i]:event[v]){
            if(t!=last){
                work(last,t,seg.query(0,n-1).ans);
                last=t;
            }
            if(i<0){
                seg.modify(~i,Monoid::unit());
            }else{
                seg.modify(i,Info{2,2-i,2+i,2});
            }
        }
        work(last,q,seg.query(0,n-1).ans);
        for(auto [t,i]:event[v]){
            seg.modify(i,Monoid::unit());
        }
    }
    multiset<int> ms;
    ms.emplace(1);
    for(int i=0;i<q;i++){
        for(auto x:upd[i]){
            if(x<0)ms.erase(ms.find(~x));
            else ms.emplace(x);
        }
        cout << (*ms.rbegin()-1)/2 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}