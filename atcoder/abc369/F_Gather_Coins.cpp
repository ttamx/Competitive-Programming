#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max-idx.hpp"

void runcase(){
    int h,w,n;
    cin >> h >> w >> n;
    vector<vector<int>> coins(h);
    for(int i=0;i<n;i++){
        int x,y;
        cin >> x >> y;
        x--,y--;
        coins[x].emplace_back(y);
    }
    SegmentTree<MaxIdxMonoid<int>> seg(w,[&](int x){return pair<int,int>(0,x);});
    vector<int> row(w,0);
    map<pair<int,int>,pair<int,int>> pre;
    for(int i=0;i<h;i++){
        sort(coins[i].begin(),coins[i].end());
        for(auto x:coins[i]){
            auto [val,idx]=seg.query(0,x);
            pre[{i,x}]={row[idx],idx};
            row[x]=i;
            seg.modify(x,pair<int,int>(val+1,x));
        }
    }
    auto [val,j]=seg.query(0,w-1);
    int i=row[j];
    string ans="";
    for(int t=i;t<h-1;t++)ans.push_back('D');
    for(int t=j;t<w-1;t++)ans.push_back('R');
    for(int t=1;t<val;t++){
        auto [ni,nj]=pre[{i,j}];
        for(;i>ni;i--)ans.push_back('D');
        for(;j>nj;j--)ans.push_back('R');
    }
    for(;i>0;i--)ans.push_back('D');
    for(;j>0;j--)ans.push_back('R');
    reverse(ans.begin(),ans.end());
    cout << val << "\n";
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}