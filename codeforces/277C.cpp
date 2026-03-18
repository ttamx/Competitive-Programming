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
    int n,m,k;
    cin >> n >> m >> k;
    map<int,vector<pair<int,int>>> ver,hor;
    for(int i=0;i<k;i++){
        int x1,y1,x2,y2;
        cin >> x1 >> y1 >> x2 >> y2;
        if(x1>x2)swap(x1,x2);
        if(y1>y2)swap(y1,y2);
        if(y1==y2)ver[y1].emplace_back(x1,x2);
        else hor[x1].emplace_back(y1,y2);
    }
    int nimsum=0;
    if((n-(int)hor.size())%2==0)nimsum^=m;
    if((m-(int)ver.size())%2==0)nimsum^=n;
    for(auto &[_,v]:hor){
        sort(v.begin(),v.end());
        int last=0,len=0;
        for(auto [l,r]:v){
            if(last>=l){
                last=max(last,r);
                continue;
            }
            len+=l-last;
            last=r;
        }
        len+=m-last;
        nimsum^=len;
    }
    for(auto &[_,v]:ver){
        sort(v.begin(),v.end());
        int last=0,len=0;
        for(auto [l,r]:v){
            if(last>=l){
                last=max(last,r);
                continue;
            }
            len+=l-last;
            last=r;
        }
        len+=n-last;
        nimsum^=len;
    }
    for(int i=1;i<n;i++)if(!hor.count(i)){
        hor[i].emplace_back(0,0);
        break;
    }
    for(int i=1;i<m;i++)if(!ver.count(i)){
        ver[i].emplace_back(0,0);
        break;
    }
    if(nimsum){
        cout << "FIRST\n";
        for(auto &[x,v]:hor){
            int last=0,len=0;
            vector<pair<int,int>> a;
            for(auto [l,r]:v){
                if(last>=l){
                    last=max(last,r);
                    continue;
                }
                a.emplace_back(last,l);
                len+=l-last;
                last=r;
            }
            a.emplace_back(last,m);
            len+=m-last;
            int req=len-(nimsum^len);
            if(req>0){
                for(auto [l,r]:a){
                    if(req>r-l){
                        req-=r-l;
                    }else{
                        cout << x << " " << 0 << " " << x << " " << l+req << "\n";
                        return;
                    }
                }
                assert(false);
            }
        }
        for(auto &[x,v]:ver){
            int last=0,len=0;
            vector<pair<int,int>> a;
            for(auto [l,r]:v){
                if(last>=l){
                    last=max(last,r);
                    continue;
                }
                a.emplace_back(last,l);
                len+=l-last;
                last=r;
            }
            a.emplace_back(last,n);
            len+=n-last;
            int req=len-(nimsum^len);
            if(req>0){
                for(auto [l,r]:a){
                    if(req>r-l){
                        req-=r-l;
                    }else{
                        cout << 0 << " " << x << " " << l+req << " " << x << "\n";
                        return;
                    }
                }
                assert(false);
            }
        }
        assert(false);
    }else{
        cout << "SECOND\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}