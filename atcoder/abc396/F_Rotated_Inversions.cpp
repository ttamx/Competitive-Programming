#include "template.hpp"
#include "data-structure/fenwick-tree.hpp"

void runcase(){
    int n,m;
    cin >> n >> m;
    vector<int> a(n);
    vector<vector<int>> pos(m+1);
    for(int i=0;i<n;i++){
        cin >> a[i];
        pos[m-a[i]].emplace_back(i);
    }
    Fenwick<int> f(m);
    ll base=0;
    for(auto x:a){
        base+=f.query(x+1,m-1);
        f.update(x,+1);
    }
    for(int i=0;i<m;i++){
        int cnt=0;
        for(auto j:pos[i]){
            base-=n-2*j-1;
            cnt++;
        }
        cout << base << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}