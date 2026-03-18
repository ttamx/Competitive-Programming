#include "template.hpp"
#include "data-structure/link-cut-tree/lazy-link-cut-tree.hpp"
#include "group/monoid-action/add-count-add.hpp"

struct Info{
    ll sum,pre,suf,ans;
};

struct InfoMonoid{
    using value_type = Info;
    static Info op(const Info &l,const Info &r){
        return Info{l.sum+r.sum,max(l.pre,l.sum+r.pre),max(l.suf+r.sum,r.suf),max({l.ans,r.ans,l.suf+r.pre})};
    }
    static Info unit(){
        return Info{0,0,0,0};
    }
};

struct ActionMonoid

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    using LCT = LazyLinkCutTree<>
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
}