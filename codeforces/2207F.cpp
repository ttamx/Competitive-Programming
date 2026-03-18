#include "template.hpp"
#include "data-structure/segment-tree/lazy-segment-tree.hpp"
#include "group/monoid-action/min-add.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<vector<int>> a(m);
    vector<int> r(n*m),c(n*m);
    for(auto &x:r)cin >> x;
    for(auto &x:c)cin >> x,x--;
    for(int i=0;i<n*m;i++){
        a[c[i]].emplace_back(r[i]);
    }
    vector<pair<int,int>> b;
    for(auto &v:a){
        reverse(v.begin(),v.end());
        vector<pair<int,int>> st;
        for(auto x:v){
            while(!st.empty()&&st.back().second<x){
                auto [r,l]=st.back();
                for(int i=l;i<=r;i++){
                    b.emplace_back(i,i);
                }
                st.pop_back();
            }
            if(!st.empty()&&st.back().second==x+1){
                st.back().second=x;
            }else{
                st.emplace_back(x,x);
            }
        }
        for(auto [r,l]:st){
            b.emplace_back(l,r);
        }
    }
    vector<vector<pair<int,int>>> event(n+2);
    for(auto [l,r]:b){
        event[l].emplace_back(l,+1);
        event[r+1].emplace_back(l,-1);
    }
    LazySegmentTree<MinAddAction<int>> seg(n+1,0);
    for(int i=1;i<=n+1;i++){
        for(auto [p,v]:event[i]){
            seg.update(0,p-1,v);
        }
        if(i>n)break;
        int dp=seg.query(0,i-1);
        seg.update(0,i-1,+1);
        seg.modify(i,dp);
    }
    cout << seg.query(0,n)-1 << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}