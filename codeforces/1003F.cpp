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
    int len=0;
    vector<string> a(n);
    for(auto &x:a){
        cin >> x;
        len+=x.size();
    }
    if(n==1){
        cout << len << "\n";
        return;
    }
    len+=n-1;
    auto b=a;
    sort(b.begin(),b.end());
    vector<int> c(n);
    for(int i=0;i<n;i++){
        c[i]=lower_bound(b.begin(),b.end(),a[i])-b.begin();
    }
    vector<int> f(n+1);
    for(int i=0;i<n;i++)f[i+1]=f[i]+a[i].size()-1;
    int ans=0;
    for(int l=0;l<n;l++){
        vector<int> pos;
        for(int i=l+1;i<n;i++){
            pos.emplace_back(i);
        }
        for(int s=1;l+s<=n;s++){
            vector<int> new_pos;
            int cnt=1,last=l;
            for(auto x:pos){
                if(x+s<=n&&c[x+s-1]==c[l+s-1]){
                    new_pos.emplace_back(x);
                    if(x>=last+s){
                        last=x;
                        cnt++;
                    }
                }
            }
            pos=move(new_pos);
            if(cnt>=2){
                ans=max(ans,cnt*(f[l+s]-f[l]+s-1));
            }
        }
    }
    cout << len-ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}