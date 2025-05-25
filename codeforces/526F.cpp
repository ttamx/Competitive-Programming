#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-count-add.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<pair<int,int>> a(n);
    for(auto &[x,y]:a){
        cin >> x >> y;
        x--,y--;
    }
    sort(a.begin(),a.end());
    vector<int> t(n,-1);
    LazySegmentTree<MinCountAddAction<int>> seg(n,make_pair(0,1));
    ll ans=0;
    for(int i=0;i<n;i++){
        int j=a[i].second;
        t[j]=i;
        seg.update(0,i,+1);
        if(j>0&&t[j-1]!=-1)seg.update(0,t[j-1],-1);
        if(j+1<n&&t[j+1]!=-1)seg.update(0,t[j+1],-1);
        ans+=seg.query(0,i).second;
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}