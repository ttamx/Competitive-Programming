#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<ll> a(n);
    vector<pair<ll,int>> vals;
    for(int i=0;i<n;i++){
        cin >> a[i];
        vals.emplace_back(a[i],i);
    }
    if(n==1){
        cout << 0 << "\n";
        return;
    }
    sort(vals.begin(),vals.end());
    for(int i=0;i<n;i++){
        a[vals[i].second]=i;
    }
    vector<ll> ans(n);
    int mn=0,mx=1;
    if(a[mn]>a[mx])swap(mn,mx);
    ll avg=(vals[a[0]].first+vals[a[1]].first)/2;
    ans[1]=max(vals[a[mx]].first-avg,vals[a[mn]].first-avg);
    Fenwick<ll> fsum(n),fcnt(n);
    for(int i=2;i<n;i++){
        if(a[i]>a[mx]){
            fsum.update(a[mx],vals[a[mx]].first);
            fcnt.update(a[mx],1);
            mx=i;
        }else if(a[i]<a[mn]){
            fsum.update(a[mn],vals[a[mn]].first);
            fcnt.update(a[mn],1);
            mn=i;
        }else{
            fsum.update(a[i],vals[a[i]].first);
            fcnt.update(a[i],1);
        }
        {
            ll l=vals[a[mn]].first,r=vals[a[mx]].first;
            while(l<r){
                ll m=(l+r)/2;
                int p=lower_bound(vals.begin(),vals.end(),make_pair(m+1,0))-vals.begin()-1;
                ll sum=vals[a[mn]].first+vals[a[mx]].first+fsum.query(p);
                ll cnt=fcnt.query(p)+2;
                if(sum<(m+1)*cnt)r=m;
                else l=m+1;
            }
            ans[i]=max(ans[i],vals[a[mx]].first-l);
        }
        {
            ll l=vals[a[mn]].first,r=vals[a[mx]].first;
            while(l<r){
                ll m=(l+r+1)/2;
                int p=lower_bound(vals.begin(),vals.end(),make_pair(m,0))-vals.begin();
                ll sum=vals[a[mn]].first+vals[a[mx]].first+fsum.query(p,n-1);
                ll cnt=fcnt.query(p,n-1)+2;
                if(sum>=m*cnt)l=m;
                else r=m-1;
            }
            ans[i]=max(ans[i],l-vals[a[mn]].first);
        }
    }
    for(auto x:ans){
        cout << x << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}