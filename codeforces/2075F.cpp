#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    auto b=a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    int m=b.size();
    for(auto &x:a){
        x=lower_bound(b.begin(),b.end(),x)-b.begin();
    }
    vector<int> ls;
    for(int i=0;i<n;i++){
        if(ls.empty()||a[i]<a[ls.back()]){
            ls.emplace_back(i);
        }
    }
    int ans=1;
    Fenwick<int> f(m);
    int st=0,ed=0;
    f.update(a[0],+1);
    auto rec=[&](auto &&self,int l,int r,int optl,int optr){
        if(l>r||optl>optr)return;
        int mid=(l+r)/2;
        int u=ls[mid];
        pair<int,int> best(-INF,optr);
        for(int i=max(u+1,optl);i<=optr;i++){
            while(ed<i){
                ed++;
                f.update(a[ed],+1);
            }
            while(st>u){
                st--;
                f.update(a[st],+1);
            }
            while(ed>i){
                f.update(a[ed],-1);
                ed--;
            }
            while(st<u){
                f.update(a[st],-1);
                st++;
            }
            best=max(best,make_pair(f.query(a[u]+1,a[i]-1)+2,i));
        }
        ans=max(ans,best.first);
        self(self,l,mid-1,optl,best.second);
        self(self,mid+1,r,best.second,optr);
    };
    rec(rec,0,ls.size()-1,0,n-1);
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}