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

ll dist(ll x1,ll y1,ll x2,ll y2){return (x1-x2)*(x1-x2)+(y1-y2)*(y1-y2);}

void runcase(){
    vector<int> a(4),b(4),x(4),y(4);
    for(int i=0;i<4;i++){
        cin >> x[i] >> y[i] >> a[i] >> b[i];
    }
    int ans=20;
    for(int i=0;i<256;i++){
        auto xx=x,yy=y;
        int res=0;
        for(int j=0;j<4;j++){
            int t=(i>>(j*2))&3;
            res+=t;
            for(int d=0;d<t;d++){
                tie(xx[j],yy[j])=make_pair(a[j]-(yy[j]-b[j]),b[j]+(xx[j]-a[j]));
            }
        }
        if(res>=ans)continue;
        bool ok=true;
        for(int i=0;i<4;i++){
            for(int j=0;j<i;j++){
                if(xx[i]==xx[j]&&yy[i]==yy[j]){
                    ok=false;
                }
            }
        }
        if(!ok)continue;
        vector<int> idx{0,1,2,3};
        do{
            if(dist(xx[idx[0]],yy[idx[0]],xx[idx[2]],yy[idx[2]])!=dist(xx[idx[1]],yy[idx[1]],xx[idx[3]],yy[idx[3]]))continue;
            ll mn=LINF,mx=0;
            for(int i=0;i<4;i++){
                int j=(i+1)%4;
                ll d=dist(xx[idx[i]],yy[idx[i]],xx[idx[j]],yy[idx[j]]);
                mn=min(mn,d);
                mx=max(mx,d);
            }
            if(mn==mx&&mn!=0){
                ans=res;
                break;
            }
        }while(next_permutation(idx.begin()+1,idx.end()));
    }
    cout << (ans<20?ans:-1) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}