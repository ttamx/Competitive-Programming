#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

const int X=5'000'000;

vector<int> prime;
int phi[X+1],lp[X+1];

struct Info{
    vector<pair<int,int>> dat;
    Info():dat(){}
    Info(int x):dat(){
        for(int i=0;;i++){
            dat.emplace_back(x,i);
            if(x==1)break;
            x=phi[x];
        }
        reverse(dat.begin(),dat.end());
    }
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &a,const Info &b){
        if(b.dat.empty())return a;
        if(a.dat.empty())return b;
        Info res;
        for(int i=0,j=0;i<a.dat.size()&&j<b.dat.size();){
            if(a.dat[i].first<b.dat[j].first){
                i++;
            }else if(a.dat[i].first>b.dat[j].first){
                j++;
            }else{
                res.dat.emplace_back(a.dat[i]);
                res.dat.back().second+=b.dat[j].second;
                i++,j++;
            }
        }
        return res;
    }
    static Info unit(){return Info();}
};

struct CustomSegmentTree:SegmentTree<Monoid>{
    using SegmentTree<Monoid>::SegmentTree;
    void edit(int l,int r,int i,int x,int v){
        if(x<l||r<x)return;
        if(t[i].dat.back().first==v){
            t[i].dat.pop_back();
        }
        for(auto &[x,y]:t[i].dat)y--;
        if(l==r)return;
        int m=(l+r)/2;
        edit(l,m,i*2,x,v);
        edit(m+1,r,i*2+1,x,v);
    }
    void edit(int x,int v){
        edit(0,n-1,1,x,v);
    }
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    CustomSegmentTree seg(n,[&](int i){return Info(a[i]);});
    set<int> s;
    for(int i=0;i<n;i++)if(a[i]!=1)s.emplace(i);
    while(q--){
        int op,l,r;
        cin >> op >> l >> r;
        l--,r--;
        if(op==1){
            for(auto it=s.lower_bound(l);it!=s.end()&&*it<=r;){
                int i=*it;
                seg.edit(i,a[i]);
                a[i]=phi[a[i]];
                if(a[i]==1){
                    it=s.erase(it);
                }else{
                    it++;
                }
            }
        }else{
            cout << seg.query(l,r).dat.back().second << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    phi[1]=1;
    for(int i=2;i<=X;i++){
        if(lp[i]==0){
            lp[i]=i;
            phi[i]=i-1;
            prime.emplace_back(i);
        }else{
            if(lp[i]==lp[i/lp[i]]){
                phi[i]=phi[i/lp[i]]*lp[i];
            }else{
                phi[i]=phi[i/lp[i]]*(lp[i]-1);
            }
        }
        for(auto p:prime){
            if(p>lp[i]||i*p>X)break;
            lp[i*p]=p;
        }
    }
    int t(1);
    while(t--)runcase();
}