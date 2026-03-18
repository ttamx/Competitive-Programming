#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    auto b=a;
    sort(b.begin(),b.end());
    b.erase(unique(b.begin(),b.end()),b.end());
    for(auto &x:a)x=lower_bound(b.begin(),b.end(),x)-b.begin();
    int k=n;
    for(;k>1;k--){
        if(n%k)continue;
        bool ok=true;
        vector<bool> mark(n);
        for(int i=0;i<n;i+=k){
            for(int j=1;j<k;j++){
                if(a[i+j-1]>a[i+j]||a[i+j]>a[i+j-1]+1){
                    ok=false;
                    break;
                }
                if(a[i+j]==a[i+j-1]+1){
                    if(mark[a[i+j-1]]){
                        ok=false;
                        break;
                    }
                    mark[a[i+j-1]]=true;
                }
            }
            if(!ok)break;
        }
        if(ok)break;
    }
    vector<int> c;
    for(int i=0;i<n;i+=k)c.emplace_back(a[i]+a[i+k-1]);
    int m=c.size();
    c.insert(c.end(),c.begin(),c.end());
    Fenwick<int> f(n*2);
    ll ans=LINF,cur=0;
    for(int i=0;i<2*m;i++){
        if(i>=m){
            ans=min(ans,cur+i-m);
            cur-=f.query(c[i-m]-1);
            f.update(c[i-m],-1);
        }
        cur+=f.query(c[i]+1,2*n-1);
        f.update(c[i],+1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t;
    cin >> t;
    while(t--)runcase();
}