#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"

struct Info{
    int open,close;
};

struct Monoid{
    using value_type = Info;
    static Info op(const Info &x,const Info &y){
        int used=min(x.open,y.close);
        return Info{x.open+y.open-used,x.close+y.close-used};
    }
    static Info unit(){return Info{0,0};}
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n),b(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        a[x]=i;
    }
    for(auto &x:b){
        cin >> x;
        x--;
    }
    SegmentTree<Monoid> seg(2*n);
    vector<int> ans(n);
    for(int i=n-1,p=0;i>=0;i--){
        seg.modify(a[i]*2,Info{1,0});
        while(p<n&&seg.t[1].open>0){
            seg.modify(b[p]*2+1,Info{0,1});
            ans[p]=i;
            p++;
        }
    }
    for(auto x:ans){
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}