#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    array<ll,2> pre,suf,sum;
    array<array<ll,4>,4> ans;
    Info():pre{0,0},suf{0,0},sum{0,0}{
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                ans[i][j]=-LINF;
            }
        }
    }
    Info(ll a,ll b):pre{max(a,0LL),max(b,0LL)},suf{max(a,0LL),max(b,0LL)},sum{a,b}{
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                ans[i][j]=a+b;
            }
        }
    }
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        Info res;
        for(int i=0;i<2;i++){
            res.pre[i]=max(l.pre[i],l.sum[i]+r.pre[i]);
            res.suf[i]=max(r.suf[i],r.sum[i]+l.suf[i]);
            res.sum[i]=l.sum[i]+r.sum[i];
        }
        for(int i=0;i<4;i++){
            for(int j=0;j<4;j++){
                res.ans[i][j]=max(res.ans[i][j],l.ans[i][j]+((j&1)?0LL:r.sum[0])+((j&2)?0LL:r.sum[1]));
                res.ans[i][j]=max(res.ans[i][j],r.ans[i][j]+((i&1)?0LL:l.sum[0])+((i&2)?0LL:l.sum[1]));
                for(int k=0;k<4;k++){
                    if(j&k)continue;
                    res.ans[i][j|k]=max(res.ans[i][j|k],l.ans[i][j]+((k&1)?r.pre[0]:0LL)+((k&2)?r.pre[1]:0LL)+(((j|k)&1)?0LL:r.sum[0])+(((j|k)&2)?0LL:r.sum[1]));
                }
                for(int k=0;k<4;k++){
                    if(i&k)continue;
                    res.ans[i|k][j]=max(res.ans[i|k][j],r.ans[i][j]+((k&1)?l.suf[0]:0LL)+((k&2)?l.suf[1]:0LL)+(((i|k)&1)?0LL:l.sum[0])+(((i|k)&2)?0LL:l.sum[1]));
                }
            }
        }
        return res;
    }
    static Info unit(){return Info();}
};

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<ll> a(n),b(n);
    for(auto &x:a){
        cin >> x;
    }
    for(auto &x:b){
        cin >> x;
    }
    SegmentTree<Monoid> seg(n,[&](int i){return Info(a[i],b[i]);});
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int i;
            ll x,y;
            cin >> i >> x >> y;
            i--;
            seg.modify(i,Info(x,y));
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            cout << seg.query(l,r).ans[3][3] << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}