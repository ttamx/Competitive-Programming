#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Monoid{
    using P = pair<int,int>;
    using value_type = P;
    static P op(const P &x,const P &y){return max(x,y);}
    static P unit(){return make_pair(0LL,-1);}
};

void runcase(){
    int n,d;
    cin >> n >> d;
    vector<ll> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    for(auto &x:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin();
    }
    vector<int> dp(n),pre(n);
    SegmentTree<Monoid> seg(n);
    for(int i=0;i<n;i++){
        int l=upper_bound(b.begin(),b.end(),b[a[i]]-d)-b.begin()-1;
        int r=lower_bound(b.begin(),b.end(),b[a[i]]+d)-b.begin();
        tie(dp[i],pre[i])=max(seg.query(0,l),seg.query(r,n));
        dp[i]++;
        seg.update(a[i],make_pair(dp[i],i));
    }
    int idx=max_element(dp.begin(),dp.end())-dp.begin();
    vector<int> ans;
    while(idx!=-1){
        ans.emplace_back(idx);
        idx=pre[idx];
    }
    reverse(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}