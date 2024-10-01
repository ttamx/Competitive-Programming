#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/add-count-add.hpp"

struct Info{
    int l,r,val;
    Info(int _l,int _r,int _val):l(_l),r(_r),val(_val){}
};

void runcase(){
    int n,k,q;
    cin >> n >> k >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    vector<ll> ans(q);
    vector<vector<pair<int,int>>> qr(n);
    for(int i=0;i<q;i++){
        int l,r;
        cin >> l >> r;
        l--,r--;
        qr[l].emplace_back(r,i);
    }
    for(int i=0;i<n;i++)a[i]-=i;
    map<int,int> cnt;
    multiset<int> ms;
    vector<int> dp(n);
    for(int i=0;i<n;i++)ms.emplace(0);
    for(int i=0;i<n;i++){
        if(i>=k){
            ms.erase(ms.find(cnt[a[i-k]]));
            cnt[a[i-k]]--;
            ms.emplace(cnt[a[i-k]]);
        }
        ms.erase(ms.find(cnt[a[i]]));
        cnt[a[i]]++;
        ms.emplace(cnt[a[i]]);
        dp[i]=*ms.rbegin();
    }
    LazySegmentTree<AddCountAddAction<ll>> seg(n);
    stack<Info> s;
    for(int l=n-k;l>=0;l--){
        Info cur(l+k-1,l+k-1,dp[l+k-1]);
        while(!s.empty()&&s.top().val<cur.val){
            auto e=s.top();
            s.pop();
            seg.update(e.l,e.r,cur.val-e.val);
            cur.r=e.r;
        }
        s.emplace(cur);
        seg.modify(cur.l,pair<ll,int>(cur.val,1));
        for(auto [r,i]:qr[l]){
            ans[i]=1LL*k*(r-l+1-k+1);
            ans[i]-=seg.query(l+k-1,r).first;
        }
    }
    for(auto x:ans)cout << x << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}