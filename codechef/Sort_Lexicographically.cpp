#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a)cin >> x;
    SegmentTree<MaxMonoid<int>> seg(a);
    vector<int> ans;
    for(int i=0;i<n;i++){
        int j=i;
        while(j+1<n&&a[j+1]>a[i])j++;
        int l=i-1,r=i;
        bool done=false;
        for(;r<j;r++){
            l=seg.findlast(0,l,[&](int x){return x>a[r+1];});
            if(l==-1){
                for(int k=i;k<r;k++){
                    ans.emplace_back(k);
                }
                for(int k=j;k>=r;k--){
                    ans.emplace_back(k);
                }
                done=true;
                break;
            }
        }
        if(!done){
            for(int k=i;k<=j;k++){
                ans.emplace_back(k);
            }
        }
        i=j;
    }
    assert(ans.size()==n);
    reverse(ans.begin(),ans.end());
    for(auto x:ans)cout << x+1 << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}