#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "data-structure/fenwick-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<int> a(n),pos(n),mark(n);
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]]=i;
    }
    for(int i=0;i<k;i++){
        int x;
        cin >> x;
        mark[x-1]=true;
    }
    SegmentTree<MinMonoid<int>> seg(a);
    Fenwick<int> fen(vector<int>(n,1));
    ll ans=0;
    for(int v=0;v<n;v++){
        if(mark[v])continue;
        int i=pos[v];
        int l=seg.findlast(0,i-1,[&](int x){return x<v;})+1;
        int r=seg.findfirst(i+1,n-1,[&](int x){return x<v;})-1;
        ans+=fen.query(l,r);
        seg.modify(i,INF);
        fen.update(i,-1);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}