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
    int n,q;
    cin >> n >> q;
    string s;
    cin >> s;
    array<array<int,3>,3> cnt{};
    set<int> st[3][3];
    for(int i=0;i<q;i++){
        char u,v;
        cin >> u >> v;
        int x=u-'a',y=v-'a';
        cnt[x][y]++;
        st[x][y].emplace(i);
    }
    for(auto &c:s){
        if(c=='a')continue;
        if(cnt[c-'a'][0]>0){
            cnt[c-'a'][0]--;
            c='a';
            continue;
        }else if(c=='c'){
            if(cnt[2][1]>0){
                cnt[2][1]--;
                c='b';
                auto it=st[2][1].begin();
                auto it2=st[1][0].upper_bound(*it);
                if(cnt[1][0]>0&&it2!=st[1][0].end()){
                    cnt[1][0]--;
                    c='a';
                    st[2][1].erase(it);
                    st[1][0].erase(it2);
                }
            }
        }else{
            if(cnt[1][2]>0&&cnt[2][0]>0){
                auto it=st[1][2].begin();
                auto it2=st[2][0].upper_bound(*it);
                if(it2!=st[2][0].end()){
                    cnt[1][2]--,cnt[2][0]--;
                    c='a';
                    st[1][2].erase(it);
                    st[2][0].erase(it2);
                }
            }
        }
    }
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}