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
    vector<int> a(n);
    int st=0;
    for(auto &x:a){
        string s;
        cin >> s;
        vector<int> pos;
        for(int i=0;i<s.size();i++){
            if(s[i]!='-'){
                pos.emplace_back(i);
            }
        }
        if(pos.empty())continue;
        if(pos.size()==1){
            if(m==1)continue;
            if(s[pos[0]]=='G'){
                st|=1;
            }else{
                st|=2;
            }
        }else if(s[pos[0]]==s[pos[1]]){
            if(pos[1]-pos[0]==1)continue;
            if(s[pos[0]]=='G'){
                st|=1;
            }else{
                st|=2;
            }
        }else{
            x=pos[1]-pos[0]-1;
        }
    }
    if(st==1){
        cout << "First\n";
        return;
    }
    if(st==2){
        cout << "Second\n";
        return;
    }
    if(st==3){
        cout << "Draw\n";
        return;
    }
    for(int i=0;i<10;i++){
        int cnt=0;
        for(auto x:a){
            if(x>>i&1){
                cnt++;
            }
        }
        if(cnt%(k+1)){
            cout << "First\n";
            return;
        }
    }
    cout << "Second\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}