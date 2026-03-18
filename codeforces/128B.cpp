#include "template.hpp"
#include "string/suffix-array.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min-idx.hpp"

void runcase(){
    string s;
    cin >> s;
    int k;
    cin >> k;
    int n=s.size();
    if(k>1LL*n*(n+1)/2){
        cout << "No such line.\n";
        return;
    }
    k--;
    SuffixArray sa(s);
    SegmentTree<MinIdxMonoid<int>> seg(n+1,[&](int i){return make_pair(sa.lcp[i],i);});
    function<bool(int,int,int)> solve=[&](int l,int r,int len){
        if(l==r){
            int gap=n-sa.sa[l]-len;
            if(k<gap){
                cout << s.substr(sa.sa[l],len+k+1) << "\n";
                return true;
            }
            k-=gap;
            return false;
        }
        auto [cur,m]=seg.query(l+1,r);
        int gap=cur-len;
        if(1LL*gap*(r-l+1)>k){
            for(int i=len+1;i<=cur;i++){
                if(k>=r-l+1){
                    k-=r-l+1;
                }else{
                    cout << s.substr(sa.sa[m],i) << "\n";
                    return true;
                }
            }
            assert(false);
        }
        k-=1LL*gap*(r-l+1);
        if(solve(l,m-1,cur))return true;
        if(solve(m,r,cur))return true;
        return false;
    };
    assert(solve(1,n,0));
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}