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

void runcase(){
    int n;
    cin >> n;
    auto ask1=[&](int x,int y){
        cout << "? " << n-2;
        for(int i=1;i<=n;i++){
            if(i!=x&&i!=y){
                cout << " " << i;
            }
        }
        cout << endl;
        int a,b;
        cin >> a >> b;
        if(a>b){
            swap(a,b);
        }
        return make_pair(a,b);
    };
    vector<pair<int,int>> cands;
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++){
            cands.emplace_back(i,j);
        }
    }
    shuffle(cands.begin(),cands.end(),rng);
    int h=n/2;
    while(cands.size()>1){
        auto [x,y]=cands.back();
        auto [a,b]=ask1(x,y);
        if(a==h&&b==h+1){
            break;
        }
        cands.pop_back();
    }
    auto [a,b]=cands.back();
    auto ask2=[&](int c,int d){
        cout << "? 4 " << a << " " << b << " " << c << " " << d << endl;
        int x,y;
        cin >> x >> y;
        if(x>y){
            swap(x,y);
        }
        return make_pair(x,y);
    };
    vector<int> pos;
    for(int i=1;i<=n;i++){
        if(i!=a&&i!=b){
            pos.emplace_back(i);
        }
    }
    vector<int> cands2;
    for(int i=0;i<pos.size();i+=2){
        int c=pos[i],d=pos[i+1];
        auto [x,y]=ask2(c,d);
        if(x==h&&y==h+1){
            cout << "! " << c << " " << d << endl;
            return;
        }
        if(x==h||x==h+1||y==h||y==h+1){
            cands2.emplace_back(c);
            cands2.emplace_back(d);
        }
    }
    assert(cands2.size()==4);
    for(int i=0;i<4;i++){
        for(int j=i+1;j<4;j++){
            int c=cands2[i];
            int d=cands2[j];
            auto [x,y]=ask2(c,d);
            if(x==h&&y==h+1){
                cout << "! " << c << " " << d << endl;
                return;
            }
        }
    }
    assert(false);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}