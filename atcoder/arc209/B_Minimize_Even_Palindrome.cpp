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
    string s;
    cin >> s;
    int n=s.size();
    vector<int> cnt(26);
    for(auto x:s){
        cnt[x-'a']++;
    }
    int mx=*max_element(cnt.begin(),cnt.end());
    if(mx*2<=n+1){
        string ans="";
        char p='.';
        for(int i=0;i<n;i++){
            int best=-1;
            char cur='.';
            for(int j=0;j<26;j++){
                char c='a'+j;
                if(c==p)continue;
                if(cnt[j]>best){
                    best=cnt[j];
                    cur=c;
                }
            }
            assert(cur!='.');
            ans.push_back(cur);
            cnt[cur-'a']--;
            p=cur;
        }
        cout << ans << "\n";
        return;
    }
    char cmx='.';
    for(char c='a';c<='z';c++){
        if(cnt[c-'a']==mx){
            cmx=c;
        }
    }
    int cut=n-mx;
    vector<int> cur(cut+1,1);
    mx-=cut+1;
    if(mx%2==1){
        mx++;
        cur[0]--;
    }
    while(mx>0){
        for(auto &x:cur){
            if(mx>=2){
                mx-=2;
                x+=2;
            }
        }
    }
    string t="";
    for(auto x:s){
        if(x!=cmx){
            t.push_back(x);
        }
    }
    string ans(cur[0],cmx);
    for(int i=0;i<cut;i++){
        ans.push_back(t[i]);
        ans+=string(cur[i+1],cmx);
    }
    cout << ans << "\n";
}

int main(){
    cin.tie(nullptr)->sync_with_stdio(false);
    int t(1);
    cin >> t;
    while(t--)runcase();
}