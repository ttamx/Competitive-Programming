#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    Fenwick<int> f(n+1),f2(n+1);
    auto ask=[&](int l,int r){
        int res;
        cout << "? " << l << " " << r << endl;
        cin >> res;
        return r-l+1-res+f.query(l,r);
    };
    vector<int> t(4*n,-1);
    function<int(int,int,int,int)> rec=[&](int l,int r,int i,int k){
        if(l==r)return l;
        int m=(l+r)/2;
        if(t[i*2]==-1){
            t[i*2]=ask(l,m);
            t[i*2+1]=t[i]-t[i*2];
        }
        if(k<=t[i*2])return rec(l,m,i*2,k);
        else return rec(m+1,r,i*2+1,k-t[i*2]);
    };
    for(int i=1;i<=n;i++){
        f2.update(i,+1);
    }
    while(q--){
        int k;
        cin >> k;
        k=f2.find(k-1);
        f2.update(k,-1);
        if(t[1]==-1)t[1]=ask(1,n);
        int p=rec(1,n,1,k);
        f.update(p,+1);
        cout << "! " << p << endl;
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}