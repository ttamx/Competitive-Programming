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
    string s,t;
    cin >> s >> t;
    vector<int> nxt(26,-1);
    for(int i=0;i<n;i++){
        int u=s[i]-'a',v=t[i]-'a';
        if(nxt[u]==-1)nxt[u]=v;
        else if(nxt[u]!=v){
            cout << -1 << "\n";
            return;
        }
    }
    int cnt=0,ans=0;
    for(int i=0;i<26;i++){
        if(nxt[i]!=-1&&nxt[i]!=i){
            ans++;
        }
    }
    vector<bool> done(26);
    for(int t=0;t<26;t++){
        for(int i=0;i<26;i++){
            if(done[i])continue;
            int j=nxt[i];
            if(j==-1||j==i||done[j]){
                if(j==-1||done[j])cnt++;
                done[i]=true;
            }
        }
    }
    int p=0;
    vector<int> id(26,-1);
    for(int i=0;i<26;i++){
        if(done[i]||id[i]!=-1)continue;
        int j=i;
        while(id[j]==-1){
            id[j]=i;
            j=nxt[j];
            assert(j!=-1);
        }
        if(id[j]==i){
            if(cnt==0){
                cout << -1 << "\n";
                return;
            }else{
                ans++;
            }
        }
    }
    cout << ans+p << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}