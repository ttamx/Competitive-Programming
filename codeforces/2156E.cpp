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
    vector<int> a(n);
    for(auto &x:a){
        cin >> x;
    }
    set<pair<int,int>> s;
    vector<tuple<int,int,int>> b;
    for(int i=0;i<n;i++){
        auto it=s.begin();
        for(int t=0;t<3&&it!=s.end();t++,it++){
            auto [v,j]=*it;
            b.emplace_back(a[i]-v,i,j);
        }
        s.emplace(a[i],i);
    }
    sort(b.rbegin(),b.rend());
    if(b.size()>15){
        b.resize(15);
    }
    vector<int> pos;
    for(auto [v,i,j]:b){
        pos.emplace_back(i);
        pos.emplace_back(j);
    }
    sort(pos.begin(),pos.end());
    pos.erase(unique(pos.begin(),pos.end()),pos.end());
    vector<bool> keep(n),del(n);
    function<int(int)> play=[&](int t){
        if(t==3){
            for(auto [v,i,j]:b){
                if((keep[i]&&!del[j])||(keep[j]&&!del[i])){
                    return v;
                }
            }
            return -INF;
        }
        if(t==1){
            int res=-INF;
            for(auto x:pos){
                if(!del[x]){
                    keep[x]=true;
                    res=max(res,play(t+1));
                    keep[x]=false;
                }
            }
            return res;
        }
        int res=INF;
        for(auto x:pos){
            if(!del[x]&&!keep[x]){
                del[x]=true;
                res=min(res,play(t+1));
                del[x]=false;
            }
        }
        return res;
    };
    cout << play(0) << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}