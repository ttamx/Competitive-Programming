#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info:array<array<bool,2>,2>{
    Info(){
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                (*this)[i][j]=false;
            }
        }
    }
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        Info res;
        for(int i=0;i<2;i++){
            for(int j=0;j<2;j++){
                for(int k=0;k<2;k++){
                    res[i][j]|=l[i][k]&&r[k][j];
                }
            }
        }
        return res;
    }
    static Info unit(){
        Info res;
        res[0][0]=res[1][1]=true;
        return res;
    }
};

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(2*n);
    for(auto &x:a)cin >> x;
    if(n%2==0){
        for(int i=0;i<n;i+=2){
            ll d1=abs(a[i]+a[i+1]-a[i+n]-a[i+n+1]);
            ll d2=abs(a[i+n]+a[i+1]-a[i]-a[i+n+1]);
            if(d2<d1){
                swap(a[i],a[i+n]);
            }
        }
        ll mn=LINF,mx=-LINF;
        for(int i=0;i<2*n;i+=2){
            ll val=a[i]+a[i+1];
            mn=min(mn,val);
            mx=max(mx,val);
        }
        cout << mx-mn << "\n";
        return;
    }
    auto getval=[&](int i,int s){
        if(s==0)return a[i];
        if(i<n)return a[i+n];
        else return a[i-n];
    };
    vector<tuple<ll,int,int,int>> vals;
    for(int i=0,u=0,v=1;i<n;i++){
        for(int j=0;j<2;j++){
            for(int k=0;k<2;k++){
                vals.emplace_back(getval(u,j)+getval(v,k),i,j,k);
            }
        }
        u=v<n?v+n:v-n;
        v=u+1;
    }
    sort(vals.begin(),vals.end());
    int m=vals.size();
    vector<Info> dat(n,Info());
    SegmentTree<Monoid> seg(dat);
    auto update=[&](int x,bool v){
        auto [_,i,j,k]=vals[x];
        dat[i][j][k]=v;
        seg.modify(i,dat[i]);
    };
    auto check=[&](){
        auto res=seg.query(0,n-1);
        return res[0][0]||res[1][1];
    };
    ll ans=LINF;
    for(int l=0,r=0;l<m;l++){
        while(r<m&&!check()){
            update(r,true);
            r++;
        }
        if(!check())break;
        ans=min(ans,get<0>(vals[r-1])-get<0>(vals[l]));
        update(l,false);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}