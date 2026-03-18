#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    Fenwick<int> f(n);
    while(q--){
        int o;
        cin >> o;
        if(o==1){
            int l,r;
            cin >> l >> r;
            l--,r--;
            f.update(l,1);
            f.update(r+1,-1);
        }else if(o==2){
            int x;
            cin >> x;
            x--;
            int val=f.query(x);
            f.update(x,-val);
            f.update(x+1,val);
            while(val--&&a[x]>9){
                int res=0;
                while(a[x]){
                    res+=a[x]%10;
                    a[x]/=10;
                }
                a[x]=res;
            }
            cout << a[x] << '\n';
        }
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}