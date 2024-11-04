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

template<class STR>
vector<int> z_algorithm(const STR &s){
    int n=(int)s.size();
    vector<int> z(n);
    z[0]=n;
    for(int i=1,l=0,r=1;i<n;i++){
        if(i<r)z[i]=min(r-i,z[i-l]);
        while(i+z[i]<n&&s[z[i]]==s[i+z[i]])z[i]++;
        if(i+z[i]>r)l=i,r=i+z[i];
    }
    return z;
}

void runcase(){
    int n,k;
    cin >> n >> k;
    int cnt=0;
    int cnt1=0,cnt2=0;
    auto work=[&](){
        vector<int> a(n);
        bool ok1=false,ok2=false;
        for(auto &x:a){
            cin >> x;
            if(x){
                cnt1++;
                ok1=true;
            }else{
                cnt2++;
                ok2=true;
            }
        }
        if(ok1)cnt++;
        if(ok2)cnt++;
        int m;
        cin >> m;
        vector<vector<int>> adj(n);
        for(int i=0;i<m;i++){
            int u,v;
            cin >> u >> v;
            u--,v--;
            adj[u].emplace_back(v);
        }
        vector<int> dep(n,-1);
        function<void(int)> dfs=[&](int u){
            for(auto v:adj[u]){
                if(dep[v]==-1){
                    dep[v]=dep[u]+1;
                    dfs(v);
                }
            }
        };
        dep[0]=0;
        dfs(0);
        vector<int> in(k),out(k);
        for(int i=0;i<n;i++){
            if(a[i]==0){
                in[dep[i]%k]++;
            }else{
                out[dep[i]%k]++;
            }
        }
        return make_pair(in,out);
    };
    auto [in1,out1]=work();
    auto [in2,out2]=work();
    if(cnt1!=cnt2){
        cout << "NO\n";
        return;
    }
    if(cnt==2){
        cout << "YES\n";
        return;
    }
    auto s1=out2,s2=out1;
    s1.insert(s1.end(),in1.begin(),in1.end());
    s1.insert(s1.end(),in1.begin(),in1.end());
    s2.insert(s2.end(),in2.begin(),in2.end());
    s2.insert(s2.end(),in2.begin(),in2.end());
    auto z1=z_algorithm(s1);
    auto z2=z_algorithm(s2);
    vector<bool> ok(k);
    for(int i=0;i<k;i++){
        if(z1[i+k]>=k){
            ok[(k+1-i)%k]=true;
        }
    }
    for(int i=0;i<k;i++){
        if(z2[i+k]>=k){
            if(ok[(k+i-1)%k]){
                cout << "YES\n";
                return;
            }
        }
    }
    cout << "NO\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}