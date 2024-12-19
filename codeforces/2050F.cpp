#include "template.hpp"
#include "data-structure/sparse-table.hpp"
#include "group/monoid/monoid-base.hpp"

int combine(int a,int b){
    return gcd(a,b);
}

int unit(){
    return 0;
}

using Mono = MonoidBase<int,combine,unit>;

void runcase(){
    int n,q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    if(n==1){
        while(q--){
            int l,r;
            cin >> l >> r;
            cout << 0 << " ";
        }
        cout << "\n";
        return;
    }
    vector<int> b(n-1);
    for(int i=0;i<n-1;i++){
        b[i]=abs(a[i]-a[i+1]);
    }
    SparseTable<Mono> st(b);
    while(q--){
        int l,r;
        cin >> l >> r;
        l--,r--;
        if(l==r){
            cout << 0 << " ";
        }else{
            cout << st.query(l,r-1) << " ";
        }
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}