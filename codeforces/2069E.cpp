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

int solve(vector<int> aa,vector<int> bb,int ab,int ba){
    int all=0,cur=0,rem=0;
    priority_queue<int,vector<int>,greater<int>> pq;
    priority_queue<int> pq2;
    for(auto x:aa){
        if(x%2==0){
            pq.emplace(x);
            rem+=x/2-1;
        }else{
            all+=x/2;
        }
    }
    for(auto x:bb){
        if(x%2==0){
            if(x>=4){
                pq2.emplace(x);
            }
            rem+=x/2;
        }else{
            all+=x/2;
        }
    }
    int res=min(ba,rem+all);
    for(int i=1;i<=ab;i++){
        if(!pq.empty()){
            int x=pq.top();
            pq.pop();
            rem-=x/2-1;
            x-=2;
            if(x>=2){
                rem+=x/2-1;
                pq.emplace(x);
            }
        }else if(all>0){
            all--;
        }else if(!pq2.empty()){
            int x=pq2.top();
            pq2.pop();
            rem-=x/2;
            x-=3;
            all+=x/2;
        }else{
            break;
        }
        res=max(res,i+min(rem+all,ba));
    }
    return res;
}

void runcase(){
    string s;
    cin >> s;
    int a,b,ab,ba;
    cin >> a >> b >> ab >> ba;
    int n=s.size();
    a=min(a,n);
    b=min(b,n);
    ab=min(ab,n/2);
    ba=min(ba,n/2);
    int ca=0,cb=0;
    for(auto &x:s){
        (x=='A'?ca:cb)++;
    }
    vector<int> aa,bb;
    for(int i=0;i<n;){
        int j=i+1;
        while(j<n&&s[j]!=s[j-1]){
            j++;
        }
        (s[i]=='A'?aa:bb).emplace_back(j-i);
        i=j;
    }
    int v=max(solve(aa,bb,ab,ba),solve(bb,aa,ba,ab));
    if(ca<=a+v&&cb<=b+v){
        cout << "YES\n";
    }else{
        cout << "NO\n";
    }
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}