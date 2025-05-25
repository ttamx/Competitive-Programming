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
    int n,k;
    cin >> n >> k;
    string s;
    cin >> s;
    int c=count(s.begin(),s.end(),'o');
    if(c==k){
        for(auto &x:s)if(x=='?')x='.';
        cout << s << "\n";
        return;
    }
    for(int i=0;i<n;i++){
        if(s[i]=='o'){
            if(i>0&&s[i-1]=='?')s[i-1]='.';
            if(i+1<n&&s[i+1]=='?')s[i+1]='.';
        }
    }
    vector<int> pos;
    for(int i=-1;i<n;i++){
        if(i>=0&&s[i]!='.')continue;
        int j=i+1;
        while(j<n&&s[j]=='?')j++;
        int sz=j-i-1;
        c+=(sz+1)/2;
        if(sz%2){
            for(int x=i+1;x<j;x+=2)pos.emplace_back(x);
        }
        i=j-1;
    }
    assert(c>=k);
    if(c==k){
        for(auto i:pos)s[i]='o';
    }
    for(int i=0;i<n;i++){
        if(s[i]=='o'){
            if(i>0&&s[i-1]=='?')s[i-1]='.';
            if(i+1<n&&s[i+1]=='?')s[i+1]='.';
        }
    }
    if(count(s.begin(),s.end(),'o')==k){
        for(auto &x:s)if(x=='?')x='.';
    }
    cout << s << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    while(t--)runcase();
}