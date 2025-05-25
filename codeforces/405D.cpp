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

const int S=1e6+5;

bool a[S],b[S];
queue<pair<int,int>> q;

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int n;
    cin >> n;
    for(int i=0;i<n;i++){
        int x;
        cin >> x;
        a[x]=1;
        b[x]=true;
    }
    int l=500000,r=500001;
    int cnt=0;
    vector<int> ans;
    while(l>0){
        if(a[l]&&a[r]){
            q.emplace(l,r);
        }else if(a[l]){
            b[r]=true;
            a[l]=false;
            ans.emplace_back(r);
        }else if(a[r]){
            b[l]=true;
            a[r]=false;
            ans.emplace_back(l);
        }else if(!q.empty()){
            auto [li,ri]=q.front();
            q.pop();
            a[li]=a[ri]=false;
            b[l]=b[r]=true;
            ans.emplace_back(l);
            ans.emplace_back(r);
        }
        l--,r++;
    }
    while(!q.empty())q.pop();
    l++,r--;
    while(l<r){
        if(a[l]&&a[r]){
            q.emplace(l,r);
        }else if(!b[l]&&!b[r]){
            assert(!a[l]&&!a[r]);
            if(!q.empty()){
                auto [li,ri]=q.front();
                q.pop();
                a[li]=a[ri]=false;
                b[l]=b[r]=true;
                ans.emplace_back(l);
                ans.emplace_back(r);
            }
        }
        l++,r--;
    }
    assert(q.empty());
    sort(ans.begin(),ans.end());
    cout << ans.size() << "\n";
    for(auto x:ans)cout << x << " ";
    cout << "\n";
}