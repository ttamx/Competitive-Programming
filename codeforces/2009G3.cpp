#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/add-count-add.hpp"

struct Info{
    ll l,r,val;
    Info(ll _l,ll _r,ll _val):l(_l),r(_r),val(_val){}
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
    LazySegmentTree<AddCountAddAction<ll>> seg(n),seg2(n,pair<ll,int>(0,1));
    stack<Info> s;
    for(int l=n-k,t=1;l>=0;l--,t++){
        Info cur(l+k-1,l+k-1,dp[l+k-1]);
        while(!s.empty()&&s.top().val<cur.val){
            auto e=s.top();
            s.pop();
            seg.update(e.l,e.r,cur.val-e.val);
            seg2.update(e.l,e.r,e.val*(t-1));
            cur.r=e.r;
        }
        s.emplace(cur);
        seg.modify(cur.l,pair<ll,int>(cur.val,1));
        seg2.update(cur.l,cur.r,-cur.val*(t-1));
        for(auto [r,i]:qr[l]){
            ans[i]=1LL*k*(r-l+1-k+1)*(r-l+1-k+2)/2;
            ans[i]-=seg.query(l+k-1,r).first*t+seg2.query(l+k-1,r).first;
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