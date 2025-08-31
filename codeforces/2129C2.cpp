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
    auto ask=[&](vector<int> a){
        cout << "? " << a.size();
        for(auto x:a){
            cout << " " << x+1;
        }
        cout << endl;
        int res;
        cin >> res;
        return res;
    };
    int s=-1;
    {
        vector<int> cands(n);
        iota(cands.begin(),cands.end(),0);
        if(ask(cands)==0){
            reverse(cands.begin(),cands.end());
        }
        int l=0,r=n-2;
        while(l<r){
            int m=(l+r+1)/2;
            if(ask(vector<int>(cands.begin()+m,cands.end()))>0)l=m;
            else r=m-1;
        }
        s=cands[l];
    }
    string ans(n,'X');
    ans[s]='(';
    int cnt=0;
    int sz=1;
    vector<int> a,id;
    auto solve=[&](){
        int res=ask(a);
        for(int i=0;i<cnt;i++){
            ans[id[i]]=(res>>i&1)?')':'(';
        }
        a.clear();
        id.clear();
        cnt=0;
        sz=1;
    };
    for(int i=0;i<n;i++){
        if(i==s)continue;
        for(int t=0;t<sz+1;t++){
            a.emplace_back(s);
        }
        for(int t=0;t<sz;t++){
            a.emplace_back(i);
        }
        id.emplace_back(i);
        sz*=2;
        cnt++;
        if(cnt==8){
            solve();
        }
    }
    if(cnt>0){
        solve();
    }
    cout << "! " << ans << endl;
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}