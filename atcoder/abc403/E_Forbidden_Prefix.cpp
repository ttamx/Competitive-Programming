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

const int N=5e5+5;
const int A=26;

int term[N],cnt[N];
int ch[N][A];
int buf=1;

void runcase(){
    int q;
    cin >> q;
    while(q--){
        int t;
        string s;
        cin >> t >> s;
        if(t==1){
            bool found=false;
            int u=1;
            for(auto x:s){
                int c=x-'a';
                if(!ch[u][c])ch[u][c]=++buf;
                u=ch[u][c];
                if(term[u]){
                    found=true;
                    break;
                }
            }
            if(!found){
                term[u]=1;
                int cc=cnt[u];
                u=1;
                cnt[u]-=cc;
                for(auto x:s){
                    int c=x-'a';
                    if(!ch[u][c])ch[u][c]=++buf;
                    u=ch[u][c];
                    cnt[u]-=cc;
                }
            }
        }else{
            bool found=false;
            int u=1;
            for(auto x:s){
                int c=x-'a';
                if(!ch[u][c])ch[u][c]=++buf;
                u=ch[u][c];
                if(term[u]){
                    found=true;
                    break;
                }
            }
            if(!found){
                u=1;
                cnt[u]++;
                for(auto x:s){
                    int c=x-'a';
                    u=ch[u][c];
                    cnt[u]++;
                }
            }
        }
        cout << cnt[1] << "\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}