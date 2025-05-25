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
    for(auto &x:a)cin >> x,x--;
    vector<int> id(n,-1);
    int root=-1;
    vector<int> cand;
    for(int i=0;i<n;i++){
        if(id[i]!=-1)continue;
        int j=i;
        while(id[j]==-1){
            id[j]=i;
            j=a[j];
        }
        if(id[j]!=i)continue;
        int k=j,cnt=0;
        do{
            cnt++;
            k=a[k];
        }while(k!=j);
        if(cnt==1&&root==-1){
            root=j;
        }else{
            cand.emplace_back(j);
        }
    }
    if(root==-1)root=cand[0];
    for(auto x:cand)a[x]=root;
    cout << cand.size() << "\n";
    for(auto x:a)cout << x+1 << " ";
    cout << "\n";

}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}