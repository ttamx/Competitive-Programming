#include "template.hpp"
#include "graph/graph-base.hpp"
#include "tree/hld.hpp"

void runcase(){
    int n;
    cin >> n;
    int a,b;
    cin >> a >> b;
    a--,b--;
    auto g=read_tree(n);
    HLD t(g);
    int d=t.dist(a,b);
    int rt=t.jump(a,b,d/2);
    HLD t2(g,rt);
    int ans=(d+1)/2+(n-1)*2-*max_element(t2.dep.begin(),t2.dep.end());
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}