#include<bits/stdc++.h>
#include<bits/extc++.h>

using namespace std;
using namespace __gnu_pbds;

template<class T>
using ordered_multiset=tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n,q,l,r;
    cin >> n >> q >> l >> r;
    l--,r--;
    ordered_multiset<int> t;
    while(n--){
        int x;
        cin >> x;
        t.insert(x);
    }
    while(q--){
        auto itl=t.find_by_order(l);
        auto itr=t.find_by_order(r);
        int x=*itl,y=*itr;
        t.erase(itl);
        t.erase(itr);
        t.insert(y-x);
        t.insert((x+y)/2);
    }
    for(auto x:t)cout << x << " ";
}