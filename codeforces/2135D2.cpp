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

const bool LOCAL=false;

void runcase(){
    int ww;
    if(LOCAL){
        cin >> ww;
    }
    auto ask=[&](const vector<int> &a){
        if(LOCAL){
            int cur=0,res=1;
            for(auto x:a){
                if(x>ww)return 0;
                if(cur+x<=ww){
                    cur+=x;
                }else{
                    res++;
                    cur=x;
                }
            }
            cerr << "RETURN " << res << "\n";
            return res;
        }else{
            cout << "? " << a.size();
            for(auto x:a)cout << " " << x;
            cout << endl;
        }
        int res;
        cin >> res;
        return res;
    };
    auto answer=[&](int x){
        cout << "! " << x << endl;
    };
    int n=7000;
    int s=130;
    int h=ask(vector<int>(n,s));
    if(h==0){
        int h=ask(vector<int>(s*s,1));
        if(LOCAL)cerr << "TOTAL1 = " << n+s*s << "\n";
        for(int w=1;w<=s;w++){
            if((s*s-1)/w+1==h){
                answer(w);
                return;
            }
        }
        assert(false);
    }
    int l=INF,r=0;
    for(int w=s;w<=100'000;w++){
        int e=w/s;
        if((n-1)/(w/s)+1==h){
            l=min(l,w);
            r=max(r,w);
        }
    }
    assert(l<=r);
    if(l==r){
        answer(l);
        return;
    }
    assert(l*2>r);
    vector<int> a;
    int cl=1,cr=r-l;
    while(cl<=cr){
        a.emplace_back(cl++);
        a.emplace_back(l);
        if(cl>cr)break;
        a.emplace_back(cr--);
        a.emplace_back(l);
    }
    if(LOCAL)cerr << "TOTAL2 = " << n+a.size() << "\n";
    int v=ask(a);
    int ans=l+a.size()-v;
    answer(ans);
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}