#include"template/Header.hpp"
#include"modular-arithmetic/MontgomeryModInt.hpp"
#include"data-structure/LazySegmentTree.hpp"
#include"monoid/MonoidBase.hpp"
#include"monoid/MonoidActionBase.hpp"

struct Info{
    mint suma,sumb,ans,len;
    Info():suma(0),sumb(0),ans(0),len(0){}
    Info(mint _suma,mint _sumb,mint _ans,mint _len):suma(_suma),sumb(_sumb),ans(_ans),len(_len){}
};

Info merge_info(Info a,Info b){
    return Info(a.suma+b.suma,a.sumb+b.sumb,a.ans+b.ans,a.len+b.len);
}

Info unit_info(){
    return Info();
}

struct Tag{
    mint a,b;
    Tag():a(0),b(0){}
    Tag(mint _a,mint _b):a(_a),b(_b){}
};

Tag merge_tag(Tag a,Tag b){
    return Tag(a.a+b.a,a.b+b.b);
}

Tag unit_tag(){
    return Tag();
}

Info apply_tag(Info a,Tag b){
    return Info(a.suma+b.a*a.len,a.sumb+b.b*a.len,a.ans+b.a*a.sumb+b.b*(a.suma+b.a*a.len),a.len);
}

using MInfo = MonoidBase<Info,merge_info,unit_info>;
using MTag = MonoidBase<Tag,merge_tag,unit_tag>;
using Mono = MonoidActionBase<MInfo,MTag,apply_tag>;

void runcase(){
    int n,q;
    cin >> n >> q;
    vm a(n),b(n);
    for(auto &x:a)cin >> x;
    for(auto &x:b)cin >> x;
    vector<Info> c(n);
    for(int i=0;i<n;i++)c[i]=Info(a[i],b[i],a[i]*b[i],1);
    LazySegmentTree<Mono> s(c);
    while(q--){
        int t;
        cin >> t;
        if(t==1){
            int l,r;
            mint v;
            cin >> l >> r >> v;
            l--,r--;
            s.update(l,r,Tag(v,0));
        }else if(t==2){
            int l,r;
            mint v;
            cin >> l >> r >> v;
            l--,r--;
            s.update(l,r,Tag(0,v));
        }else{
            int l,r;
            cin >> l >> r;
            l--,r--;
            cout << s.query(l,r).ans << "\n";
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}