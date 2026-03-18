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
    vector<int> a(n),c(n);
    for(auto &x:a)cin >> x;
    for(auto &x:c)cin >> x;
    vector<int> l(n),r(n);
    {
        vector<int> st;
        for(int i=0;i<n;i++){
            while(!st.empty()&&a[st.back()]<=a[i]){
                st.pop_back();
            }
            l[i]=st.empty()?-1:st.back();
            st.emplace_back(i);
        }
    }
    {
        vector<int> st;
        for(int i=n-1;i>=0;i--){
            while(!st.empty()&&a[st.back()]<=a[i]){
                st.pop_back();
            }
            r[i]=st.empty()?n:st.back();
            st.emplace_back(i);
        }
    }
    ll base=0;
    vector<tuple<int,int,int>> upd;
    for(int i=0;i<n;i++)upd.emplace_back(c[i],l[i]+1,r[i]-1);
    sort(upd.begin(),upd.end());
    vector<int> b(n);
    set<int> s;
    for(int i=0;i<n;i++){
        s.emplace(i);
    }
    for(auto [v,l,r]:upd){
        for(auto it=s.lower_bound(l);it!=s.end()&&*it<=r;it=s.erase(it)){
            b[*it]=v;
            base+=v;
        }
    }
    s.clear();
    for(int i=0;i<n;i++){
        s.emplace(i);
    }
    priority_queue<pair<int,int>> pq;
    int mx=*max_element(a.begin(),a.end());
    for(int i=0;i<n;i++){
        if(a[i]==mx){
            pq.emplace(b[i],i);
        }
    }
    cout << base-pq.top().first << " ";
    vector<bool> used(n);
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        x--;
        for(auto it=s.lower_bound(l[x]+1);it!=s.end()&&*it<r[x];it=s.erase(it)){
            base-=b[*it];
            used[*it]=true;
        }
        while(!pq.empty()&&used[pq.top().second]){
            pq.pop();
        }
        cout << base-(pq.empty()?0:pq.top().first) << " ";
    }
    cout << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}