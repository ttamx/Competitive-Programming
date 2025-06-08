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
    string s;
    cin >> s;
    vector<tuple<int,int,int,int>> a;
    for(int l=0;l<n;l++){
        if(s[l]!='?')continue;
        int r=l;
        while(r+1<n&&s[r+1]=='?')r++;
        if(l>0&&s[l-1]=='1'&&r+1<n&&s[r+1]=='1'){
            for(int i=l;i<=r;i++){
                a.emplace_back(0,r-l,0,i);
            }
        }else if(l>0&&s[l-1]=='1'){
            for(int i=l;i<=r;i++){
                a.emplace_back(1,i-l,0,i);
            }
        }else if(r+1<n&&s[r+1]=='1'){
            for(int i=r;i>=l;i--){
                a.emplace_back(1,r-i,1,i);
            }
        }else{
            for(int i=l;i<=r;i++){
                a.emplace_back(2,l-r,0,i);
            }
        }
        l=r;
    }
    sort(a.begin(),a.end());
    int cur=1,cnt=0;
    for(auto &x:s){
        if(x=='?')x='0';
        if(x=='1')cnt++;
    }
    for(int i=0;i+1<n;i++){
        cur+=s[i]!=s[i+1];
    }
    vector<int> ans(n+1,-1);
    ans[cnt]=cur;
    for(auto [x,y,z,i]:a){
        cnt++;
        if(i>0&&s[i]!=s[i-1])cur--;
        if(i+1<n&&s[i]!=s[i+1])cur--;
        s[i]='1';
        if(i>0&&s[i]!=s[i-1])cur++;
        if(i+1<n&&s[i]!=s[i+1])cur++;
        ans[cnt]=cur;
    }
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}