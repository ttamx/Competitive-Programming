#include<bits/stdc++.h>
#define all(x) (x).begin(),(x).end()
#define rall(x) (x).rbegin(),(x).rend()

using namespace std;

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

struct node;
using pnode = node*;
struct node{
    int val;
    pnode l,r;
    node(int val):val(val),l(nullptr),r(nullptr){}
};

int n,q;
map<int,pnode> mp;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    cin >> n;
    pnode head=nullptr,pre=nullptr;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        pnode cur=new node(x);
        if(i==0){
            head=cur;
        }else{
            pre->r=cur;
            cur->l=pre;
        }
        pre=cur;
        mp[x]=cur;
    }
    cin >> q;
    while(q--){
        int op;
        cin >> op;
        if(op==1){
            int x,y;
            cin >> x >> y;
            pnode cur=new node(y);
            pnode pre=mp[x];
            cur->r=pre->r;
            if(cur->r)cur->r->l=cur;
            pre->r=cur;
            cur->l=pre;
            mp[y]=cur;
        }else{
            int x;
            cin >> x;
            pnode cur=mp[x];
            if(cur->l){
                cur->l->r=cur->r;
            }else{
                head=cur->r;
            }
            if(cur->r)cur->r->l=cur->l;
        }
    }
    for(pnode cur=head;cur;cur=cur->r){
        cout << cur->val << " ";
    }
}