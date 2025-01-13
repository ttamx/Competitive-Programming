#include "template.hpp"
#include "data-structure/sparse-table.hpp"

struct Monoid{
    using value_type = int;
    static int op(const int &x,const int &y){return gcd(x,y);}
    static int unit(){return 0;}
};

void runcase(){
    int n;
    cin >> n;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    vector<pair<int,int>> vals;
    for(int i=0;i<n;i++){
        vals.emplace_back(a[i],i);
    }
    sort(vals.begin(),vals.end());
    SparseTable<Monoid> st(a);
    int q;
    cin >> q;
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        int g=st.query(l,r);
        int cnt=upper_bound(vals.begin(),vals.end(),make_pair(g,r))-lower_bound(vals.begin(),vals.end(),make_pair(g,l));
        cout << r-l+1-cnt << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}