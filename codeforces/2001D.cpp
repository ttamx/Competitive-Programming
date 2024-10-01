#include "template.hpp"
#include "data-structure/segment-tree/segment-tree.hpp"
#include "group/monoid/min.hpp"

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    vector<queue<int>> pos(n);
    vector<int> last(n,-1);
    set<int> num;
    for(int i=0;i<n;i++){
        cin >> a[i];
        a[i]--;
        pos[a[i]].emplace(i);
        last[a[i]]=i;
        num.emplace(a[i]);
    }
    set<int> rs;
    SegmentTree<MinMonoid<int>> seg(n,INF);
    for(auto x:num){
        rs.emplace(last[x]);
        seg.modify(x,pos[x].front());
    }
    int m=rs.size();
    cout << m << "\n";
    for(int i=0,p=0;i<m;i++){
        int mn=*rs.begin();
        int x;
        if(i&1){
            x=seg.findfirst(0,n-1,[&](int x){return x<=mn;});
        }else{
            x=seg.findlast(0,n-1,[&](int x){return x<=mn;});
        }
        int cur=pos[x].front();
        while(!pos[x].empty())pos[x].pop();
        seg.modify(x,INF);
        for(;p<=cur;p++){
            int v=a[p];
            if(pos[v].empty())continue;
            pos[v].pop();
            assert(!pos[v].empty());
            seg.modify(v,pos[v].front());
        }
        rs.erase(last[x]);
        cout << x+1 << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}