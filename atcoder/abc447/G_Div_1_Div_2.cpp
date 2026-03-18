#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    ll val;
    int x,y;
};

struct T{
    Info mx,mx2,mx3;
    T(Info v):mx(v),mx2{-LINF,-1,-1},mx3{-LINF,-1,-1}{}
    T():mx{-LINF,-1,-1},mx2{-LINF,-1,-1},mx3{-LINF,-1,-1}{}
    void update(Info v){
        assert(v.val<=mx.val);
        if(v.x!=mx.x&&v.y!=mx.x&&v.val>mx2.val)mx2=v;
        if(v.x!=mx.y&&v.y!=mx.y&&v.val>mx3.val)mx3=v;
    }
    ll get(int i){
        if(i==mx.x)return mx2.val;
        if(i==mx.y)return mx3.val;
        return mx.val;
    }
};

struct Monoid{
    using value_type = T;
    static T op(T x,T y){
        if(x.mx.val<y.mx.val)swap(x,y);
        x.update(y.mx);
        x.update(y.mx2);
        x.update(y.mx3);
        return x;
    }
    static T unit(){
        return T(Info{-LINF,-1,-1});
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<int> b(n);
    for(int i=0;i<n;i++){
        cin >> b[i] >> a[i];
        b[i]--;
    }
    SegmentTree<Monoid> seg(n);
    vector<T> suf(n);
    multiset<pair<int,int>,greater<pair<int,int>>> ms;
    vector<int> opt(n);
    for(int i=n-1;i>=0;i--){
        vector<pair<ll,int>> c;
        for(auto [x,y]:ms){
            if(y==b[i])continue;
            c.emplace_back(x,y);
            if(c.size()==3)break;
        }
        if(c.size()>=2){
            suf[i].mx=Info{a[i]+c[0].first+c[1].first,c[0].second,c[1].second};
            if(c.size()==3){
                suf[i].update(Info{a[i]+c[0].first+c[2].first,c[0].second,c[2].second});
                suf[i].update(Info{a[i]+c[1].first+c[2].first,c[1].second,c[2].second});
            }
        }
        if(a[i]>opt[b[i]]){
            if(opt[b[i]])ms.erase(ms.find({opt[b[i]],b[i]}));
            ms.emplace(opt[b[i]]=a[i],b[i]);
        }
    }
    ms.clear();
    opt.assign(n,0LL);
    ll ans=-1;
    for(int i=0;i<n;i++){
        vector<pair<ll,int>> c;
        for(auto [x,y]:ms){
            if(y==b[i])continue;
            c.emplace_back(x,y);
            if(c.size()==3)break;
        }
        if(suf[i].mx.val>0){
            int x=suf[i].mx.x,y=suf[i].mx.y;
            vector<int> pos{x,y,b[i]};
            sort(pos.begin(),pos.end());
            if(pos[0]>0)ans=max(ans,seg.query(0,pos[0]-1).get(b[i])+suf[i].mx.val);
            if(pos[0]+1<pos[1])ans=max(ans,seg.query(pos[0]+1,pos[1]-1).get(b[i])+suf[i].mx.val);
            if(pos[1]+1<pos[2])ans=max(ans,seg.query(pos[1]+1,pos[2]-1).get(b[i])+suf[i].mx.val);
            if(pos[2]+1<n)ans=max(ans,seg.query(pos[2]+1,n).get(b[i])+suf[i].mx.val);
            if(suf[i].mx2.val>0)ans=max(ans,seg.query(x,x).get(b[i])+suf[i].mx2.val);
            if(suf[i].mx3.val>0)ans=max(ans,seg.query(y,y).get(b[i])+suf[i].mx3.val);
        }
        if(c.size()>=2){
            T cur(Info{a[i]+c[0].first+c[1].first,c[0].second,c[1].second});
            if(c.size()==3){
                cur.update(Info{a[i]+c[0].first+c[2].first,c[0].second,c[2].second});
                cur.update(Info{a[i]+c[1].first+c[2].first,c[1].second,c[2].second});
            }
            seg.update(b[i],cur);
        }
        if(a[i]>opt[b[i]]){
            if(opt[b[i]])ms.erase(ms.find({opt[b[i]],b[i]}));
            ms.emplace(opt[b[i]]=a[i],b[i]);
        }
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}