#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
        x--;
    }
    vector<int> last(n,-1),nxt(n,-1),dp(n);
    SegmentTree<MinMonoid<int>> seg(n,[](int i){return i;});
    int pos=0;
    for(int i=0;i<n;i++){
        int p=last[a[i]];
        if(p!=-1&&p>=pos){
            while(seg.query(p+1,i)<p){
                int x=nxt[pos];
                if(x!=-1){
                    seg.modify(x,x);
                }
                pos++;
            }
            seg.modify(i,p);
            nxt[p]=i;
        }
        last[a[i]]=i;
        dp[i]=pos;
    }
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        cout << (l>=dp[r]?"YES":"NO") << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}