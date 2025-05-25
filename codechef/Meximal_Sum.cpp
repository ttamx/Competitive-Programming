#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<int> pre_mex(n),suf_mex(n);
    {
        int mex=0;
        vector<bool> seen(n+1);
        for(int i=0;i<n;i++){
            if(a[i]<=n)seen[a[i]]=true;
            while(seen[mex])mex++;
            pre_mex[i]=mex;
        }
    }
    {
        int mex=0;
        vector<bool> seen(n+1);
        for(int i=n-1;i>=0;i--){
            if(a[i]<=n)seen[a[i]]=true;
            while(seen[mex])mex++;
            suf_mex[i]=mex;
        }
    }
    vector<queue<int>> pos(n+1);
    for(int i=0;i<n;i++){
        if(a[i]<=n){
            pos[a[i]].emplace(i);
        }
    }
    vector<int> l(n+1,n),r(n+1,-1);
    for(int i=0;i<n;i++){
        r[suf_mex[i]]=i;
    }
    for(int i=n-1;i>=0;i--){
        l[suf_mex[i]]=i;
    }
    vector<ll> qs(n);
    for(int i=0;i<n;i++){
        qs[i]=a[i];
        if(i>0){
            qs[i]+=qs[i-1];
        }
    }
    int mex=0,cur=0;
    vector<int> cnt(n+1,0);
    SegmentTree<MinMonoid<int>> seg(n+1,0);
    auto insert=[&](int i){
        int x=a[i];
        if(x>n)return;
        assert(x>=0&&x<=n);
        cnt[x]++;
        seg.modify(x,cnt[x]);
        mex=seg.findfirst(0,n,[&](int v){return v<=0;});
    };
    auto erase=[&](int i){
        int x=a[i];
        if(x>n)return;
        assert(x>=0&&x<=n);
        cnt[x]--;
        seg.modify(x,cnt[x]);
        mex=seg.findfirst(0,n,[&](int v){return v<=0;});
    };
    bool found=false;
    ll min_ans=LINF,max_ans=-LINF;
    for(int i=0;i<n-1;i++){
        if(a[i]<=n){
            assert(!pos[a[i]].empty());
            pos[a[i]].pop();
        }
        if(i==cur){
            cur++;
        }else{
            erase(i);
        }
        if(i+1==cur){
            insert(i+1);
            cur++;
        }
        while(cur<n&&mex<pre_mex[i]){
            insert(cur);
            cur++;
        }
        if(mex==pre_mex[i]&&l[mex]<n){
            int st=max(cur,l[mex])-1;
            assert(mex>=0&&mex<=n);
            int ed=(pos[mex].empty()?n:pos[mex].front())-1;
            ed=min(ed,r[mex]-1);
            if(st<=ed){
                assert(0<=st&&st<=ed&&ed<n);
                min_ans=min(min_ans,qs[st]-qs[i]);
                max_ans=max(max_ans,qs[ed]-qs[i]);
                found=true;
            }
        }
    }
    if(!found){
        cout << -1 << " " << -1 << "\n";
    }else{
        ll sum=0;
        for(auto x:a){
            sum+=x;
        }
        cout << sum-max_ans*2 << " " << sum-min_ans*2 << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}