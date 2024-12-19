#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min-idx.hpp"

ll safe_mul(ll a,ll b){
    return min(__int128_t(a)*b,__int128_t(1e18+1));
}

struct DualSegTree{
    int n;
    vector<ll> lz;
    DualSegTree(int _n){
        n=_n;
        lz.assign(4*n,1LL);
    }
    void update(int l,int r,int i,int x,int y,ll v){
        if(y<l||r<x)return;
        if(x<=l&&r<=y)return void(lz[i]=safe_mul(lz[i],v));
        int m=(l+r)/2;
        update(l,m,i*2,x,y,v);
        update(m+1,r,i*2+1,x,y,v);
    }
    void update(int x,int y,ll v){
        update(0,n-1,1,x,y,v);
    }
    ll query(int l,int r,int i,int x){
        if(l==r)return lz[i];
        int m=(l+r)/2;
        if(x<=m)return safe_mul(query(l,m,i*2,x),lz[i]);
        else return safe_mul(query(m+1,r,i*2+1,x),lz[i]);
    }
    ll query(int x){
        return query(0,n-1,1,x);
    }
};

struct DS{
    vector<pair<ll,int>> a;
    void init(ll v){
        a.emplace_back(v,0);
    }
    void merge(const DS &o){
        vector<pair<ll,int>> b;
        auto push=[&](ll v,int c){
            if(!b.empty()&&b.back().first==v){
                b.back().second=min(b.back().second,c);
                return;
            }
            while(!b.empty()&&b.back().second>=c){
                b.pop_back();
            }
            b.emplace_back(v,c);
        };
        for(int i=0,j=0;i<a.size()&&j<o.a.size();){
            if(j==o.a.size()||(i<a.size()&&a[i].first>=o.a[j].first)){
                push(a[i].first,a[i].second+o.a[j].second);
                i++;
            }else{
                push(o.a[j].first,a[i].second+o.a[j].second);
                j++;
            }
        }
        a=move(b);
    }
    void apply(ll d){
        vector<pair<ll,int>> b;
        auto push=[&](ll v,int c){
            if(!b.empty()&&b.back().first==v){
                if(b.back().second>c){
                    b.back().second=c;
                    return true;
                }
                return false;
            }
            while(!b.empty()&&b.back().second>=c){
                b.pop_back();
            }
            b.emplace_back(v,c);
            return true;
        };
        priority_queue<pair<ll,int>> pq;
        for(auto [v,c]:a){
            pq.emplace(v,-c);
        }
        while(!pq.empty()){
            auto [v,c]=pq.top();
            pq.pop();
            c=-c;
            if(push(v,c)&&v>1){
                pq.emplace((v-1)/d+1,-(c+1));
            }
        }
        a=move(b);
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    vector<int> ord(n),rank(n);
    iota(ord.begin(),ord.end(),0);
    sort(ord.begin(),ord.end(),[&](int i,int j){
        return b[i]<b[j]||(b[i]==b[j]&&a[i]>a[j]);
    });
    for(int i=0;i<n;i++){
        rank[ord[i]]=i;
    }
    SegmentTree<MinIdxMonoid<int>> smn(n,[&](int i){return make_pair(rank[i],i);});
    vector<DS> dp(n);
    for(int i=0;i<n;i++){
        dp[i].init(a[i]);
    }
    int ans=0;
    auto rec=[&](auto &&self,int l,int r)->int {
        if(l>r)return -1;
        int m=smn.query(l,r).second;
        int lch=self(self,l,m-1);
        int rch=self(self,m+1,r);
        if(lch!=-1)dp[m].merge(dp[lch]);
        if(rch!=-1)dp[m].merge(dp[rch]);
        dp[m].apply(b[m]);
        return m;
    };
    int root=rec(rec,0,n-1);
    cout << dp[root].a.back().second << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}