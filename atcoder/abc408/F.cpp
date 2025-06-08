#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,d,r;
    cin >> n >> d >> r;
    vector<int> pos(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        pos[x]=i;
    }
    vector<int> dp(n);
    SegmentTree<MaxMonoid<int>> seg(n,0);
    for(int i=0;i<n;i++){
        if(i-d>=0)seg.update(pos[i-d],dp[i-d]);
        dp[i]=seg.query(pos[i]-r,pos[i]+r)+1;
    }
    cout << *max_element(dp.begin(),dp.end())-1 << "\n";
}