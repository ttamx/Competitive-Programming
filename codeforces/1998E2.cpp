#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/max.hpp"

void runcase(){
    int n,k;
    cin >> n >> k;
    vector<ll> a(n);
    for(auto &x:a)cin >> x;
    auto qs=a;
    for(int i=1;i<n;i++)qs[i]+=qs[i-1];
    SegmentTree<MaxMonoid<ll>> seg_l(n,[&](int i){return (i>0?a[i-1]+qs[i-1]:LINF);});
    SegmentTree<MaxMonoid<ll>> seg_r(n,[&](int i){return (i+1<n?a[i+1]:LINF)-qs[i];});
    vector<int> b(n);
    vector<pair<int,int>> c(n);
    for(int i=0;i<n;i++){
        int j=seg_r.findfirst(i,n-1,[&](ll x){return x>-(i?qs[i-1]:0LL);});
        while(j<n&&qs[j]-(i?qs[i-1]:0)<(i?a[i-1]:LINF)){
            b[i]++;
            if(j+1<n)b[j+1]--;
            j=seg_r.findfirst(j+1,n-1,[&](ll x){return x>-(i?qs[i-1]:0LL);});
        }
    }
    for(int i=1;i<n;i++)b[i]+=b[i-1];
    c[0]={b[0],1};
    for(int i=1;i<n;i++){
        if(b[i]==c[i-1].first){
            c[i]=c[i-1];
            c[i].second++;
        }else{
            c[i]=min(c[i-1],{b[i],1});
        }
    }
    for(int i=k-1;i<n;i++){
        int j=seg_l.findfirst(1,i,[&](ll x){return x>qs[i];})-1;
        cout << c[min(j,i)].second << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}