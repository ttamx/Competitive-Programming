#include<bits/stdc++.h>
#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

using ll = long long;
using db = long double;
using vi = vector<int>;
using vl = vector<ll>;
using vd = vector<db>;
using pii = pair<int,int>;
using pll = pair<ll,ll>;
using pdd = pair<db,db>;
const int INF=0x3fffffff;
// const int MOD=1000000007;
const int MOD=998244353;
const ll LINF=0x1fffffffffffffff;
const db DINF=numeric_limits<db>::infinity();
const db EPS=1e-9;
const db PI=acos(db(-1));

template<class T>
using ordered_set = tree<T,null_type,less<T>,rb_tree_tag,tree_order_statistics_node_update>;
template<class T>
using ordered_multiset = tree<T,null_type,less_equal<T>,rb_tree_tag,tree_order_statistics_node_update>;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
mt19937_64 rng64(chrono::steady_clock::now().time_since_epoch().count());

struct Node;
using Ptr = Node*;
struct Node{
    int val;
    Ptr l,r;
    Node(int v):val(v),l(),r(){}
};

void runcase(){
    int q;
    cin >> q;
    vector<Ptr> ptr(q+1,nullptr);
    ptr[0]=new Node(0);
    for(int i=1;i<=q;i++){
        int op;
        cin >> op;
        if(op==1){
            int x;
            cin >> x;
            ptr[i]=new Node(i);
            ptr[i]->l=ptr[x];
            ptr[i]->r=ptr[x]->r;
            ptr[i]->l->r=ptr[i];
            if(ptr[i]->r)ptr[i]->r->l=ptr[i];
        }else{
            int p,q;
            cin >> p >> q;
            if(ptr[p]->l==ptr[q]||ptr[p]->r==ptr[q]){
                cout << 0 << "\n";
                continue;
            }
            Ptr l1=ptr[p],r1=ptr[p];
            Ptr l2=ptr[q],r2=ptr[q];
            ll ans=0;
            while(true){
                if(l1&&l1==r2){
                    swap(l1,l2);
                    swap(r1,r2);
                }
                if(r1&&r1==l2){
                    r1=r1->l;
                    while(r1!=ptr[p]&&r1!=ptr[q]){
                        ans+=r1->val;
                        r1=r1->l;
                    }
                    while(l2!=ptr[p]&&l2!=ptr[q]){
                        ans+=l2->val;
                        l2=l2->r;
                    }
                    r1->r=l2;
                    l2->l=r1;
                    break;
                }
                if(l1)l1=l1->l;
                if(r1)r1=r1->r;
                swap(l1,l2);
                swap(r1,r2);
            }
            cout << ans << "\n";
        }
    }

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}